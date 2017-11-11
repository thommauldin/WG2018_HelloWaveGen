connect -url tcp:127.0.0.1:3121
targets -set -nocase -filter {name =~ "microblaze*#0" && bscan=="USER2"  && jtag_cable_name =~ "Digilent Arty S7 - 50 210352A6BE66A"} -index 0
rst -processor
targets -set -nocase -filter {name =~ "microblaze*#0" && bscan=="USER2"  && jtag_cable_name =~ "Digilent Arty S7 - 50 210352A6BE66A"} -index 0
dow C:/Users/Thomas/Documents/GitHub/Hello_World3/Hello_World3.sdk/Hello_WaveGen/Debug/Hello_WaveGen.elf
targets -set -nocase -filter {name =~ "microblaze*#0" && bscan=="USER2"  && jtag_cable_name =~ "Digilent Arty S7 - 50 210352A6BE66A"} -index 0
con
