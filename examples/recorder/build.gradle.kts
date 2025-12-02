plugins {
    id("libgdx-oboe-example")
}

android {
    namespace = "barsoosayque.libgdxoboe.recorder"

    defaultConfig {
        applicationId = "barsoosayque.libgdxoboe.recorder"
        namespace = "barsoosayque.libgdxoboe.recorder"
    }

    compileOptions {
        sourceCompatibility = JavaVersion.VERSION_17
        targetCompatibility = JavaVersion.VERSION_17
    }
}

kotlin{
    jvmToolchain(17)
}