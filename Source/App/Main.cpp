import be.engine;
import be.platform;
import be.scene;

int main()
{
    be::SokolApp::Desc desc;
    desc.width = 1280;
    desc.height = 720;
    desc.title = "BlockEngine";

    be::Engine engine;
    engine.SetSceneProfile(be::SceneProfile::Runtime);
    engine.Run(desc);

    return 0;
}
