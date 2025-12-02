plugins {
    id("libgdx-oboe-example")
}

android {
    namespace = "barsoosayque.libgdxoboe.sounds"

    defaultConfig {
        applicationId = "barsoosayque.libgdxoboe.sounds"
        namespace = "barsoosayque.libgdxoboe.sounds"
    }
    compileOptions {
        sourceCompatibility = JavaVersion.VERSION_17
        targetCompatibility = JavaVersion.VERSION_17
    }
}

kotlin{
    jvmToolchain(17)
}