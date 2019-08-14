帧头，帧尾，CRC，数据长度，主设备类型，区域，帧ID
// 判断帧头
if(帧头 == FE)
{
	// 判断帧尾
	if(帧尾 == 0D0A0D0A0D0A)
	{
		// 判断CRC
		if(CRC == crc)
		{
			//判断数据长度
			if(长度 == length)
			{
				//判断是否是该区
				if(xx区 == EEPROM.read(区))
				{
					//判断主设备
					if(xx主设备 == C002)
					{
						判断
						if()
						{
							
						}
					}
					else
					{
						// 不是自己的主设备
					}
				}
				else
				{
					// 不是自己的区
				}
			}
		}
		else
		{
			
		}
	}
	else
	{
		
	}
}
else
{
	
}
FE A020 0E C002 00 01 C003 01 0001 0103050000 00 0D0A0D0A0D0A