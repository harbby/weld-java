package weld;

public class WeldContext extends WeldManaged {

    public WeldContext(WeldConf weldConf) {
        super(WeldJNI.weld_context_new(weldConf.handle));
    }

    @Override
    protected void doClose() {
        WeldJNI.weld_context_free(this.handle);
    }
}
