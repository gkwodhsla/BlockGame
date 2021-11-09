package com.example.blockgame;

import android.content.Context;
import android.content.res.AssetManager;
import android.graphics.PixelFormat;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;
import android.util.Log;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.view.View;

import androidx.constraintlayout.widget.ConstraintSet;

import javax.microedition.khronos.egl.EGL10;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.egl.EGLContext;
import javax.microedition.khronos.egl.EGLDisplay;
import javax.microedition.khronos.opengles.GL10;

public class GLESView extends GLSurfaceView
{
    private static final String TAG = "GLES3JNI";
    private static final boolean DEBUG = true;

    public GLESView(Context context)
    {
        super(context);
        // Pick an EGLConfig with RGB8 color, 16-bit depth, no stencil,
        // supporting OpenGL ES 2.0 or later backwards-compatible versions.
        setEGLConfigChooser(8, 8, 8, 0, 16, 0);
        setEGLContextClientVersion(3);
        setRenderer(new Renderer());
        GLESNativeLib.readAssetsNative(getContext().getAssets());
    }

    public boolean onTouchEvent(final MotionEvent e)
    {
        switch (e.getAction())
        {
            case MotionEvent.ACTION_DOWN:
                GLESNativeLib.touchEventStart(e.getX(0), e.getY(0));
                break;

            case MotionEvent.ACTION_MOVE:
                GLESNativeLib.touchEventMove(e.getX(0), e.getY(0));
                break;

            case MotionEvent.ACTION_UP:
                GLESNativeLib.touchEventRelease(e.getX(0), e.getY(0));
                break;
        }
        return true;
    }

    private static class Renderer implements GLSurfaceView.Renderer
    {
        public void onDrawFrame(GL10 gl){ GLESNativeLib.draw();}

        public void onSurfaceChanged(GL10 gl, int width, int height) { GLESNativeLib.resize(width, height); }

        public void onSurfaceCreated(GL10 gl, EGLConfig config) {GLESNativeLib.init(); }

    }
}