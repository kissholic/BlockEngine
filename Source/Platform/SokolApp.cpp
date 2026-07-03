module;
#include <cstdint>
#include "sokol_app.h"
#include "sokol_gfx.h"
#include "sokol_glue.h"
#include "sokol_time.h"
#include "sokol_log.h"
#include "sokol_gl.h"
#include "imgui.h"
#include "util/sokol_imgui.h"

module be.platform;

namespace be {

SokolApp* SokolApp::sInstance = nullptr;

void SokolApp::Init(IAppDelegate* delegate, const Desc& desc)
{
    mDelegate = delegate;
    sInstance = this;
    mWidth = desc.width;
    mHeight = desc.height;

    sapp_desc sdesc = {};
    sdesc.init_cb = InitCallback;
    sdesc.frame_cb = FrameCallback;
    sdesc.cleanup_cb = CleanupCallback;
    sdesc.event_cb = EventCallback;
    sdesc.width = static_cast<int>(desc.width);
    sdesc.height = static_cast<int>(desc.height);
    sdesc.window_title = desc.title;
    sdesc.sample_count = desc.sampleCount;
    sdesc.high_dpi = false;
    sdesc.logger.func = slog_func;

    sapp_run(&sdesc);
}

void SokolApp::BeginFrame() {}
void SokolApp::EndFrame() {}

void SokolApp::InitCallback()
{
    sg_desc sgdesc = {};
    sgdesc.environment = sglue_environment();
    sgdesc.logger.func = slog_func;
    sg_setup(&sgdesc);

    stm_setup();

    sgl_desc_t sgldesc = {};
    sgldesc.logger.func = slog_func;
    sgl_setup(&sgldesc);

    simgui_desc_t simdesc = {};
    simgui_setup(&simdesc);

    sInstance->mLastTime = stm_now();
    sInstance->mDelegate->OnAppInit();
}

void SokolApp::FrameCallback()
{
    std::uint64_t now = stm_now();
    sInstance->mDeltaTime = stm_sec(stm_diff(now, sInstance->mLastTime));
    sInstance->mLastTime = now;
    sInstance->mFrameCount++;

    simgui_frame_desc_t simframe = {};
    simframe.width = sapp_width();
    simframe.height = sapp_height();
    simframe.delta_time = sInstance->mDeltaTime;
    simframe.dpi_scale = sapp_dpi_scale();
    simgui_new_frame(&simframe);

    sInstance->mDelegate->OnAppFrame();

    sg_pass_action pass_action = {};
    pass_action.colors[0].load_action = SG_LOADACTION_CLEAR;
    pass_action.colors[0].clear_value = {0.15f, 0.15f, 0.18f, 1.0f};

    sg_pass pass = {};
    pass.action = pass_action;
    pass.swapchain = sglue_swapchain();
    sg_begin_pass(&pass);

    sgl_draw();
    simgui_render();

    sg_end_pass();
    sg_commit();
}

void SokolApp::CleanupCallback()
{
    sInstance->mDelegate->OnAppCleanup();
    simgui_shutdown();
    sgl_shutdown();
    sg_shutdown();
}

void SokolApp::EventCallback(const sapp_event* ev)
{
    sInstance->mLastEvent = ev;
    if (simgui_handle_event(ev)) return;
    sInstance->mDelegate->OnAppEvent(ev);
}

} // namespace be
