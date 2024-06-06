# Metronome Project

## Description

This project transforms an Arduino board and shield into a metronome, which is an essential tool for musicians to practice timing. The [metronome](https://www.youtube.com/watch?v=n3QfM7LdmAo&ab_channel=LearnPianowithJazerLee) provides a short sound or light flash (or both) at a predefined frequency. The flash, sound, and frequency can be configured at startup, and the behavior can be modified during operation using buttons. The speed is displayed on a 7-segment display.

## Operation

When the Arduino starts, it begins operating with the following initial predefined values:

- **Beat Frequency**: 60 beats per minute (bpm), displayed on the 7-segment display.
- **Beat Representation**: A short low buzzer sound.

### Button Functions

- **Button 1**: Decrease tempo.
- **Button 2**: Pause and display statistics.
- **Button 3**: Increase tempo.
- **Potentiometer**: Adjust the sound frequency through the buzzer (higher or lower frequency).

### Mode Switching

By pressing **Button 1** and **Button 3** together for more than 1 second, the metronome mode switches in the following order:

1. **Sound Mode**: Only the buzzer is used for beats.
2. **LED Mode**: Only the LEDs are used for beats.
3. **Sound & LED Mode**: Both buzzer and LEDs are used for beats.
4. **Dot Mode**: The display is blanked, and ticks are shown using just one point (dp) on the display.

### Display Behavior

- The display shows the speed in bpm during one beat.
- It then shows the approximate tempo name during the next beat.
- Example: Initially, the display alternates between `60 → Lento → 60 → Lento`.

### Pause Functionality (Button 2)

When the pause button is pressed:

- Statistics are sent to the serial monitor.
- Example output:

```text
10s 60 bpm buzzer Lento
5s 65 bpm buzzer Lento
7s 75 bpm LEDs Adagio
```

- Pressing Button 2 again resumes the metronome.

## Tempo Classification Table

![Tempo Marking](https://violinspiration.com/wp-content/uploads/Tempo-Meaning-BPM.jpg)

> Source: [What are the most common Italian Tempo Markings?](https://violinspiration.com/free-online-metronome/)

## Requirements

- **Statistics Storage**: Statistics are stored in an array of structs, allocated on the heap.
- **Predefined Tempos**: The table with predefined tempos is stored in an array.
- **Timers**: A timer is used to generate the beat at the correct time, and another timer is used to refresh the display.
- **Button Interrupts**: Button presses are handled using interrupts.

## Additional Details

### Timer Configuration

- **Timer0**: Configured for a 2kHz interrupt (0.5ms interval) to manage the beat frequency.
- **Timer1**: Configured for a 1Hz interrupt (1 second interval) to manage the display refresh rate.
- **Timer2**: Configured for an 8kHz interrupt (0.125ms interval) to handle finer sound control.

### Interrupts

- **Button 1** (Decrease tempo) is connected to an external interrupt that decreases the bpm by 5 with each press.
- **Button 2** (Pause) toggles the metronome operation and sends statistics to the serial monitor.
- **Button 3** (Increase tempo) is connected to an external interrupt that increases the bpm by 5 with each press.
- **Combination of Button 1 and Button 3**: Toggles between different operational modes when pressed together for more than 1 second.

### Statistics

- Each time the metronome's state is paused, a snapshot of the current bpm, mode, and tempo name is stored in a struct.
- These statistics are maintained in an array and are sent to the serial monitor upon request.

### Display

- The 7-segment display shows the bpm and the tempo name alternately.
- The potentiometer adjusts the frequency of the buzzer sound, allowing for customization of the metronome's auditory feedback.

### Operational Modes

1. **Sound Mode**: The metronome uses a buzzer to indicate the beat.
2. **LED Mode**: LEDs flash to indicate the beat.
3. **Sound & LED Mode**: Both the buzzer and LEDs indicate the beat.
4. **Dot Mode**: The display is blanked, and a single dot indicates the beat.

### Potentiometer Control

- Adjusts the frequency of the buzzer sound for a higher or lower pitch.
- This feature allows users to customize the sound according to their preference.

### Challenges and Problems

- Memory Management: Allocating and freeing memory dynamically for the statistics array to prevent memory leaks.
- Interrupt Handling: Managing button presses and timer interrupts effectively to ensure accurate timing and responsive controls.
- Mode Switching: Implementing smooth transitions between different operational modes when buttons are pressed together.
