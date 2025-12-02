plugins {
    id("libgdx-oboe-example")
}

android {
    namespace = "barsoosayque.libgdxoboe.waves"

    defaultConfig {
        applicationId = "barsoosayque.libgdxoboe.waves"
        namespace = "barsoosayque.libgdxoboe.waves"
    }
    compileOptions {
        sourceCompatibility = JavaVersion.VERSION_17
        targetCompatibility = JavaVersion.VERSION_17
    }
}

kotlin{
    jvmToolchain(17)
}