#!/bin/sh
mkdir -p ../burn
echo "//IT IS A BURN FILE. DO NOT EDIT." > ../burn/burn.ino
cat i2clcd.ino >> ../burn/burn.ino
cat clock.ino >> ../burn/burn.ino
cat events.ino >> ../burn/burn.ino
cat adc.ino >> ../burn/burn.ino
cat display.ino >> ../burn/burn.ino
cat encoder.ino >> ../burn/burn.ino
cat logic.ino >> ../burn/burn.ino
cat main.ino >> ../burn/burn.ino
