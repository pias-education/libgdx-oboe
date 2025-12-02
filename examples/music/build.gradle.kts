plugins {
    id("libgdx-oboe-example")
}

android {
    namespace = "barsoosayque.libgdxoboe.music"

    defaultConfig {
        applicationId = "barsoosayque.libgdxoboe.music"
        namespace = "barsoosayque.libgdxoboe.music"
    }
    compileOptions {
        sourceCompatibility = JavaVersion.VERSION_17
        targetCompatibility = JavaVersion.VERSION_17
    }
}

kotlin{
    jvmToolchain(17)
}