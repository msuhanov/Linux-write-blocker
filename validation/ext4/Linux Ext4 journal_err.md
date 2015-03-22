# Case: Linux Ext4 journal_err
## Requirements
- Oracle VM VirtualBox;
- Grml 2014.11;
- Kali 1.1.0a.

## Description
The *Linux Ext4 journal_err.ova* file contains a virtual machine with two drives making up an Ext4 file system with external journaling. There is an error recorded in the journal on */dev/sdb1*, and the Ext4 file system driver will transfer an error code from the journal to the primary superblock of the file system on */dev/sda1* during the mount operation (unless you specify the "noload" mount option) – see *Fig. 1* (data modifications on the block devices marked as read-only) and *Fig. 2-3* (data modifications on the block device with the journal not protected by a read-only loop device).

<img src="https://raw.githubusercontent.com/msuhanov/Linux-write-blocker/master/validation/ext4/images/1.png" alt="Fig. 1" /><br>*Fig. 1*<br>

<img src="https://raw.githubusercontent.com/msuhanov/Linux-write-blocker/master/validation/ext4/images/2.png" alt="Fig. 2" /><br>*Fig. 2*<br>

<img src="https://raw.githubusercontent.com/msuhanov/Linux-write-blocker/master/validation/ext4/images/3.png" alt="Fig. 3" /><br>*Fig. 3*

### Grml 2014.11
Grml 2014.11 includes the kernel patch available in this repository along with their own userspace tools to mark block devices as read-only (in the *Forensic Mode*). When block devices are marked as read-only, no data modifications from file system drivers are allowed, and an error code recorded in the journal of the Ext4 file system will not be transferred to the primary superblock (*Fig. 4*).

<img src="https://raw.githubusercontent.com/msuhanov/Linux-write-blocker/master/validation/ext4/images/4.png" alt="Fig. 4" /><br>*Fig. 4*
