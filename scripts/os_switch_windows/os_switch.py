import psutil
import win32api
from io import StringIO
import os
from os import system

def run():
    uf = StringIO()
    num=0
    while True:
        disk_list = []
        last_num=num
        for item in psutil.disk_partitions():
            # 判断是不是U盘
            if "removable" in item.opts:
                # 获取U盘的盘符
                disk_list.append(item.mountpoint)
        num=len(disk_list)
        if(num!=last_num):
        # 把盘符写入内存，为了不持续请求
            if disk_list != []:
                for pf in disk_list:            
                        #print(f"U盘序列号:{win32api.GetVolumeInformation(pf)[1]} ")
                        if win32api.GetVolumeInformation(pf)[1] == 1437231394 :
                            #print(f"U盘序列号:{win32api.GetVolumeInformation(pf)} {pf} ")
                            with open(str(pf)+'switch_position') as file_obj:
                                content = file_obj.read()
                                if content == "0" :
                                    #print(content)
                                    # 重启
                                    system("shutdown -r -t 10")
                                
                        # print (str(disk_list[1])+"switch_position")
            else:
                # 拔出u盘初始化内存
                uf = StringIO('hello')
                #print("U盘拔出")


if __name__ == "__main__":
    run()