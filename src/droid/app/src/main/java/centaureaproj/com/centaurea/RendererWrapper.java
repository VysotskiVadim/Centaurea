package centaureaproj.com.centaurea;

import android.app.Activity;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.opengl.GLES30;
import android.opengl.GLSurfaceView;
import android.opengl.GLUtils;

import javax.microedition.khronos.opengles.GL10;

import static android.opengl.GLES10.glClear;
import static android.opengl.GLES10.glClearColor;
import static android.opengl.GLES20.GL_COLOR_BUFFER_BIT;

public class RendererWrapper implements GLSurfaceView.Renderer {

    private GameLibJNIWrapper jniWrapper;

    public RendererWrapper(GameLibJNIWrapper jniWrapper) {
        this.jniWrapper = jniWrapper;
    }

    @Override
    public void onSurfaceCreated(GL10 gl10, javax.microedition.khronos.egl.EGLConfig eglConfig) {
        jniWrapper.on_surface_created();
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        jniWrapper.on_surface_changed(width, height);
    }

    @Override
    public void onDrawFrame(GL10 gl) {
        jniWrapper.on_draw_frame();
    }
}
