import be.engine;
import be.platform;

int main()
{
    be::SokolApp::Desc desc;
    desc.width = 1280;
    desc.height = 720;
    desc.title = "BlockEngine";

    be::Engine engine;
    engine.Run(desc);

    return 0;
}
