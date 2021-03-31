# HW02
將按鈕放到麵包板上面，將UP鈕接上pin D10，DOWN鈕接上pin D9，CONFIRM鈕接上pin D8。
按鈕正極接3.3V，負極串連一個電阻在接地。
再將電容接上麵包版串聯兩個電阻，將電容一邊接地，測試另一側的跨壓，此處的V_in是來自板子上DAC的輸出，所以要把正極接到pin D7。
由low pass filter 輸出的電壓，要給picoscope測量，還要接到pin D12，當作AnalogIn再把傳進來的電壓資料給FFT.py來跑。
先將程式灌進去板子上，先用UP跟DOWN調整頻率，在輸入"sudo python3 FFT.py"，才能按下CONFIRM。

![image](https://user-images.githubusercontent.com/72737928/113104942-a722df80-9233-11eb-91ac-30462cc00446.png)
