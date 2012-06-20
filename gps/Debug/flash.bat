@echo off
cls
avrdude -c avrisp2 -p m32 -P com9 -u -U flash:w:gps.hex
pause