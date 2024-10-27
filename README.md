# scanf checker GCC plugin

This plugin reports unsafe calls to scanf. For example, `scanf("%s", buf)`
is just as unsafe as `gets(buf)` yet no compiler warns about it as of 2024.

## Building

    meson setup _build
    cd _build
    meson compile

Then try out the plugin using

    gcc -fplugin=./scanf_checker.so ../test/vulnerable.c
