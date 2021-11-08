package com.example.blockgame;

import android.app.Activity;
import android.content.res.AssetManager;
import android.os.Bundle;
import android.util.Log;
import android.view.WindowManager;

import java.io.File;

public class GLESActivity extends Activity
{
    GLESView view;
    @Override protected void onCreate(Bundle bundle)
    {
        super.onCreate(bundle);
        view = new GLESView(getApplication());
        setContentView(view);
    }

    @Override protected void onPause()
    {
        super.onPause();
        view.onPause();
    }

    @Override protected void onResume()
    {
        super.onResume();
        view.onResume();
    }
}
