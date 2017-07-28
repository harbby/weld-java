package weld;

public class Weld {
  private Weld() {}

  public static void loadLibrary(String filename) {
    WeldError error = new WeldError();
    WeldJNI.weld_load_library(filename, error.handle);
    if (error.getCode() != 0) {
      final WeldException e = new WeldException(error);
      error.close();
      throw e;
    }
  }
}
