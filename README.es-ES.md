

# Zopa Drum Machine
Este es un sencillo [secuenciador](https://en.wikipedia.org/wiki/Music_sequencer) para Android. Aquí aprovechamos todo el poder de la **recién lanzada** [librería de audio google oboe c++](https://github.com/google/oboe) con Kotlin.
![image](https://i.imgur.com/6anttIk.png)

# Zopa Piano
También puedes encontrar aquí una implementación sencilla de un Piano generado con la función de onda `Sin`.
![piano](https://i.imgur.com/5PexIr4.png)

# Zopa MediaPlayer with waveform playback controller
Un reproductor multimedia sencillo con una forma de onda visualizada. Además, puedes cambiar fácilmente el progreso de reproducción actual. El progreso de reproducción adopta la forma de la forma de onda actual.
![mediaplayer](https://i.imgur.com/ccZwHod.png)


# Zopa MediaPlayer with waveform visualization
Vista personalizada `FrequencyView.kt` con un espectro de frecuencias visualizado para el progreso de reproducción actual. Cada contenedor (bin) corresponde a un rango de frecuencias. El más a la izquierda representa las frecuencias más bajas, el más a la derecha la frecuencia más alta, y las frecuencias medias están en el centro de la vista.

[![Wavefor](http://img.youtube.com/vi/2vuc9vSd9fw/0.jpg)](http://www.youtube.com/watch?v=2vuc9vSd9fw "Wavefor")

*Haz clic en la imagen para reproducir el video de YouTube*

#### Características
- Secuenciador
    - Secuenciador de 16 pasos
    - Kick/Snare/Clap como archivos wav, por lo que puedes cambiarlos por tus propios sonidos.
    - Guardado/carga automática del estado
- Piano
    - Piano multitáctil generado por la función de onda `Sin`
    - Ondas `square_wave`, `downward_sawtooth_wave`, `upward_sawtooth_wave`, `triangle_wave` disponibles, consulta más en `SimpleOscillator.h` 

Además, puedes encontrar en el repositorio una implementación sencilla del efecto de retraso (`SimpleDelay.h`) y del oscilador (`SimpleOscillator.h`).
