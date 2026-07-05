import be.engine;
import be.platform;
import be.render;
import be.scene;
import be.editor;

int main()
{
    be::SokolApp::Desc desc;
    desc.width = 1280;
    desc.height = 720;
    desc.title = "BlockEngine — Editor";

    be::Engine engine;
    be::Editor editor;

    engine.SetSceneProfile(be::SceneProfile::Editor);

    editor.SetFocusCallback(
        [&engine](unsigned entityId)
        {
            engine.FocusEntity(entityId);
        });

    engine.SetEditorInitCallback(
        [&editor]()
        {
            editor.InitImGui();
        });

    engine.SetEditorDrawCallback(
        [&editor](const be::FrameSnapshot::DebugUI* debug)
        {
            editor.Draw(debug);
        });

    editor.Init();
    engine.Run(desc);
    editor.Shutdown();

    return 0;
}
