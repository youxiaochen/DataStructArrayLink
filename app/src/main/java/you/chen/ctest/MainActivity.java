package you.chen.ctest;

import android.os.Bundle;
import android.view.View;

import androidx.appcompat.app.AppCompatActivity;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {

    static {
        System.loadLibrary("native");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        findViewById(R.id.bt0).setOnClickListener(this);
        findViewById(R.id.bt1).setOnClickListener(this);
        findViewById(R.id.bt2).setOnClickListener(this);
        findViewById(R.id.bt3).setOnClickListener(this);
        findViewById(R.id.bt4).setOnClickListener(this);
        findViewById(R.id.bt5).setOnClickListener(this);
        findViewById(R.id.bt6).setOnClickListener(this);
    }

    @Override
    public void onClick(View v) {
        switch (v.getId()) {
            case R.id.bt0:
                test0();
                break;
            case R.id.bt1:
                test1();
                break;
            case R.id.bt2:
                test2();
                break;
            case R.id.bt3:
                test3();
                break;
            case R.id.bt4:
                test4();
                break;
            case R.id.bt5:
                test5();
                break;
            case R.id.bt6:
                test6();
                break;
        }
    }

    public native void test0();

    public native void test1();

    public native void test2();

    public native void test3();

    public native void test4();

    public native void test5();

    public native void test6();

}
