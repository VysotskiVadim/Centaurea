package centaureaproj.com.centaurea;

import android.app.Activity;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.opengl.GLES30;
import android.opengl.GLUtils;

public class GameLibJNIWrapper {

    private Activity activity;

    public GameLibJNIWrapper(Activity activity) {
        this.activity = activity;
    }

    static {
        System.loadLibrary("androidgame");
    }

    public native void on_surface_created();

    public native void on_surface_changed(int width, int height);

    public native void on_draw_frame();


    public void loadImageToGlTexture(String name) {
        int id = activity.getResources().getIdentifier("texture_" + name, "drawable", activity.getPackageName());
        Bitmap bitmap = BitmapFactory.decodeResource(activity.getResources(), id);
        GLUtils.texImage2D(GLES30.GL_TEXTURE_2D, 0, bitmap, 0);
        bitmap.recycle();
    }
}