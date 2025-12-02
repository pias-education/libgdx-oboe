plugins {
    id("libgdx-oboe-example")
}

android {
    namespace = "barsoosayque.libgdxoboe.async"

    defaultConfig {
        applicationId = "barsoosayque.libgdxoboe.async"
        namespace = "barsoosayque.libgdxoboe.async"
    }

    compileOptions {
        sourceCompatibility = JavaVersion.VERSION_17
        targetCompatibility = JavaVersion.VERSION_17
    }

}
 kotlin{
     jvmToolchain(17)
 }