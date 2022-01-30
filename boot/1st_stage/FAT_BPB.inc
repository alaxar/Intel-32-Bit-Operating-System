
; BIOS Parameter Block

OEM_Identifier:	    	db	"ETHIOPIC"
BytesPerSector:		    dw	512
NoSecPerCluster:    	db	1
NoReservedSec:  		dw	1
NoFATTables:    		db	2
NoRootDirectories:  	dw	224
TotalNoSectors: 		dw	2880
MediaTypeDesc:  		db	0xF0
NumberofSectorsPerFat:	dw	9
NumberofSectorsPerTrack dw  18
NumberOfHeader: 		dw  2
NumberOfHiddenSec:  	dd  0
LargeSectorCount:   	dd  0


; Extended BIOS Parameter Block

drive_number:           db  0
Reserved:               db  0
Signature:              db  0x29
Volume_id:              db "ETH", 0x00
Volume_label:           db "ETHIOPICOS", 0x00
System_identifier:      db "FAT12   ",