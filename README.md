# 7Zip Compressor
GUI frontend for a command-line-based 7-zip archiver/compressor using QT GUI toolkit and C++. User is able to select files that will be archived and specify the output archive's path.

## The application has following features:
- The list of input files can be modified by using the "Add files" and "Remove all files" buttons (implemented in the project template - see a link placed in the Hints).
- Output files can be specified using the "Browse" file picker control (also implemented in the template).
- Command-line 7z compressor will be invoked as a subprocess after clicking the "Compress!" button.
- All standard output/input and error streams will be redirected from the controlled subprocess (7za.exe) to the parent process (GUI frontend).
- During the compressor's operation, all appropriate GUI controls will be disabled, and the application's status shown in the status bar will be updated in accordance with the current application's state.
- The compressor's output messages will be displayed by using MessageBox() function just after the termination of the controlled subprocess or continuously during its operation.

<img width="240" alt="image" src="https://github.com/bhusal-ujjwal/7ZipCompressor/assets/45995959/fe2b751d-9346-4086-8848-29d6fa875015">
