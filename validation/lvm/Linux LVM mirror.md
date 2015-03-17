# Case: Linux LVM mirror
## Requirements
- Oracle VM VirtualBox;
- Grml 2014.11;
- another live forensic distribution of your choice.

## Description
The *Linux LVM mirror.ova* file contains a virtual machine with two drives making up a mirrored Linux LVM set. The drives are out of sync, i.e. their contents represent different states of a logical volume being mirrored. In particular, the out-of-date volume on */dev/sda1* contains a text file that was deleted in the up-to-date volume on */dev/sdb1* (*Fig. 1*).

<img src="https://raw.githubusercontent.com/msuhanov/Linux-write-blocker/master/validation/lvm/images/1.png" alt="Fig. 1" /><br>*Fig. 1*

Several popular live forensic distributions automatically activate LVM volumes (when running in the forensic / write blocking mode), thus triggering their synchronization if required (*Fig. 2-3*).

<img src="https://raw.githubusercontent.com/msuhanov/Linux-write-blocker/master/validation/lvm/images/2.png" alt="Fig. 2" /><br>*Fig. 2*<br><br>
<img src="https://raw.githubusercontent.com/msuhanov/Linux-write-blocker/master/validation/lvm/images/3.png" alt="Fig. 3" /><br>*Fig. 3*

This results in a text file on */dev/sda1* being implicitly deleted by the LVM driver (*Fig. 4*).

<img src="https://raw.githubusercontent.com/msuhanov/Linux-write-blocker/master/validation/lvm/images/4.png" alt="Fig. 4" /><br>*Fig. 4*

### Grml 2014.11
Grml 2014.11 includes the kernel patch available in this repository along with their own userspace tools to mark block devices as read-only (in the *Forensic Mode*). Since no LVM volumes are being automatically activated by Grml 2014.11 in the forensic mode, we need to activate them manually. As you can see (*Fig. 5*), Grml 2014.11 successfully blocks write requests going to the drives, and the data remains untouched. Note that write requests were issued to the read-only block devices!

<img src="https://raw.githubusercontent.com/msuhanov/Linux-write-blocker/master/validation/lvm/images/5.png" alt="Fig. 5" /><br>*Fig. 5*
