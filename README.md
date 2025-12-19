# libGDX Oboe

[![libGDX](https://img.shields.io/badge/libGDX-1.13.1-yellow.svg)](https://github.com/libgdx/libgdx/releases/tag/1.13.1)
[![oboe](https://img.shields.io/badge/oboe-1.9.3-yellow.svg)](https://github.com/google/oboe/releases/tag/1.9.3)

<table><tr>
<td><img src="/icon.png" align="center" width="250" alt="Icon"></td>
<td>
    
Reimplementation of the Audio interface for **libGDX** framework using [Oboe][oboe] and [FFmpeg][ffmpeg], which allows music to flow without any delay or another unpleasant distortion.

And if you ever asked yourself *"Why is my libGDX app music is so broken ?"*, then you've come to the right place.

</td>
</tr>
<tr>
    <td colspan="2">
    
        <b>Caution: no FFmpeg bundle</b><br>
        This fork of libgdx-oboe does <b>not</b> ship FFmpeg binaries.<br>
        FFmpeg <b>must be built separately per ABI</b> and placed into the project. Currently used FFmpeg version: 5.1.4
        <br>
        Reasons:
        <ul>
            <li>ABI stability</li>
            <li>avoiding prebuilt binary mismatch</li>
            <li>support for legacy ARMv7 devices</li>
            <li>avoid ELF/strip issues</li>
            <li>developer controls codec selection & size</li>
        </ul>
        
    </td>
</tr>

</table>

## Docs

- 🔰 [How to Use][usage]
- 🏗️ [How to Build][build]
- 🎺 [Explore Examples][examples]

## Quick example

To use the library, you'll have to add it as a dependency and override the default audio engine on android:

```kotlin
class AndroidLauncher : AndroidApplication() {
    // Magic happens here:
    override fun createAudio(context: Context, config: AndroidApplicationConfiguration): AndroidAudio =
            OboeAudio(context.assets)

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        // Create an app like always
        val config = AndroidApplicationConfiguration()
        initialize(SomeApp(), config)
    }
}
```

## How does the library work

Using [Oboe library][oboe] from Google you can create high-performance audio streams that may tweak some features in runtime to boost performance even further.
These streams are native, so there is no GC that will slow things down.
For audio decoding this library provide native tools: *libavformat* with MP3, OGG and WAV support only (but you can [build it yourself][build] to support more audio formats).
Such audio decoder is blazing fast and precise so combining that with oboe streams, we get responsive and fast `Audio` implementation.

## Features

Here is a table of known goodies and problems for certain features per file format (decoder):

|Feature|State|Description|
|-------|-----|-----------|
|Sounds|⭐|Per-sound soundpools. All features should be working. Although max sounds isn't read from android config, the number is infinite at the moment.
|Music playing|⭐|Precise position, starts and pauses exactly when requested.|
|Music Seek|👌|_WAV_ is precise, no content lost. _OGG_ and _MP3_ is different: bad initial seek, but dropping frames until PTS is equal to desired seek TS. May lose some content if PTS isn't precise enough.|
|Audio Device|👌|Repetitive writes to audio device might produce audio artifacts (cracks).|
|Audio Recorder|👌|Repetitive reads bleed a little bit of cache from the last read to the buffer. Omit a few first frames when using recorded PCM.|

*⭐ Works well* \
*👌 It's alright in general but may have corner cases*

[oboe]: https://github.com/google/oboe
[libgdx]: https://github.com/libgdx/libgdx
[ffmpeg]: https://ffmpeg.org
[usage]: /docs/Usage.md
[examples]: /docs/Examples.md
[build]: /docs/Build.md
