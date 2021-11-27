package com.example.blockgame;

import android.content.res.AssetManager;

public class GLESNativeLib
{
    static
    {
        System.loadLibrary("gles3jni");
    }
    public static native void init();
    public static native void resize(int width, int height);
    public static native void draw(float deltaTime);
    public static native void readAssetsNative(AssetManager AM);
    public static native void touchEventStart(float x, float y);
    public static native void touchEventMove(float x, float y);
    public static native void touchEventRelease(float x, float y);
    public static native void pause();
    public static native void resume();
}
