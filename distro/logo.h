#ifndef LOGO_H
#define LOGO_H

const char *arch[] = {
	"                   -`\t\t\t",
	"                  .o+`\t\t\t",
	"                 `ooo/\t\t\t",
	"                `+oooo:\t\t\t",
	"               `+oooooo:\t\t",
	"               -+oooooo+:\t\t",
	"             `/:-:++oooo+:\t\t",
	"            `/++++/+++++++:\t\t",
	"           `/++++++++++++++:\t\t",
	"          `/+++ooooooooooooo/`\t\t",
	"         ./ooosssso++osssssso+`\t\t",
	"        .oossssso-````/ossssss+`\t",
	"       -osssssso.      :ssssssso.\t",
	"      :osssssss/        osssso+++.\t",
	"     /ossssssss/        +ssssooo/-\t",
	"   `/ossssso+/:-        -:/+osssso+-\t",
	"  `+sso+:-`                 `.-/+oso:\t",
	" `++:.                           `-/+/\t",
	" .`                                 `\t"
},
	*debian[] = {
	"       _,met$$$$$gg.\t\t",
	"    ,g$$$$$$$$$$$$$$$P.\t\t",
	"  ,g$$P\"     \"\"\"Y$$.\".\t\t",
	" ,$$P'              `$$$.\t",
	"',$$P       ,ggs.     `$$b:\t",
	"`d$$'     ,$P\"'   .    $$$\t",
	" $$P      d$'     ,    $$P\t",
	" $$:      $$.   -    ,d$$'\t",
	" $$;      Y$b._   _,d$P'\t",
	" Y$$.    `.`\"Y$$$$P\"'\t\t",
	" `$$b      \"-.__\t\t",
	"  `Y$$\t\t\t\t",
	"   `Y$$.\t\t\t",
	"     `$$b.\t\t\t\t",
	"       `Y$$b.\t\t\t",
	"          `\"Y$b._\t\t",
	"              `\"\"\"\t"
},
	*kali[] = {
 "..............\t\t\t\t\t",
 "            ..,;:ccc,.\t\t\t\t",
 "          ......''';lxO.\t\t\t",
 ".....''''..........,:ld;\t\t\t",
 "           .';;;:::;,,.x,\t\t\t",
 "      ..'''.            0Xxoc:,.  ...\t\t",
 "  ....                ,ONkc;,;cokOdc',.\t\t",
 " .                   OMo           ':\x1b[1m\033[37mdd\x1b[1m\033[34mo.\t",
 "                    dMc               :OO;\t",
 "                    0M.                 .:o.\t",
 "                    ;Wd\t\t\t\t",
 "                     ;XO,\t\t\t",
 "                       ,d0Odlc;,..\t\t",
 "                           ..',;:cdOOd::,.\t",
 "                                    .:d;.':;.\t",
 "                                       'd,  .'\t",
 "                                         ;l   ..",
 "                                          .o",
 "                                            c",
 "                                            .'",
 "                                             ."
},
	*manjaro[] = {
	" ██████████████████  ████████\t",
	" ██████████████████  ████████\t",
	" ██████████████████  ████████\t",
	" ██████████████████  ████████\t",
	" ████████            ████████\t",
	" ████████  ████████  ████████\t",
	" ████████  ████████  ████████\t",
	" ████████  ████████  ████████\t",
	" ████████  ████████  ████████\t",
	" ████████  ████████  ████████\t",
	" ████████  ████████  ████████\t",
	" ████████  ████████  ████████\t",
	" ████████  ████████  ████████\t",
	" ████████  ████████  ████████\t"
},
	*mint[] = {
	"\x1b[1m\033[37m             ...-:::::-...\x1b[1m\033[32m\t\t\t",
	"\x1b[1m\033[37m          .-MMMMMMMMMMMMMMM-.\x1b[1m\033[32m\t\t\t",
	"\x1b[1m\033[37m      .-MMMM\x1b[1m\033[37m`..-:::::::-..`\x1b[1m\033[37mMMMM-.\x1b[1m\033[32m\t\t",
	"\x1b[1m\033[37m    .:MMMM\x1b[1m\033[37m.:MMMMMMMMMMMMMMM:.\x1b[1m\033[37mMMMM:.\x1b[1m\033[32m\t\t",
	"\x1b[1m\033[37m   -MMM\x1b[1m\033[32m-M---MMMMMMMMMMMMMMMMMMM.\x1b[1m\033[37mMMM-\x1b[1m\033[32m\t\t",
	"\x1b[1m\033[37m `:MMM\x1b[1m\033[32m:MM`  :MMMM:....::-...-MMMM:\x1b[1m\033[37mMMM:`\x1b[1m\033[32m\t\t",
	"\x1b[1m\033[37m :MMM\x1b[1m\033[32m:MMM`  :MM:`  ``    ``  `:MMM:\x1b[1m\033[37mMMM:\x1b[1m\033[32m\t\t",
	"\x1b[1m\033[37m.MMM\x1b[1m\033[32m.MMMM`  :MM.  -MM.  .MM-  `MMMM.\x1b[1m\033[37mMMM.\x1b[1m\033[32m\t",
	"\x1b[1m\033[37m:MMM\x1b[1m\033[32m:MMMM`  :MM.  -MM-  .MM:  `MMMM-\x1b[1m\033[37mMMM:\x1b[1m\033[32m\t",
	"\x1b[1m\033[37m:MMM\x1b[1m\033[32m:MMMM`  :MM.  -MM-  .MM:  `MMMM:\x1b[1m\033[37mMMM:\x1b[1m\033[32m\t",
	"\x1b[1m\033[37m:MMM\x1b[1m\033[32m:MMMM`  :MM.  -MM-  .MM:  `MMMM-\x1b[1m\033[37mMMM:\x1b[1m\033[32m\t",
	"\x1b[1m\033[37m.MMM\x1b[1m\033[32m.MMMM`  :MM:--:MM:--:MM:  `MMMM.\x1b[1m\033[37mMMM.\x1b[1m\033[32m\t",
	"\x1b[1m\033[37m :MMM\x1b[1m\033[32m:MMM-  `-MMMMMMMMMMMM-`  -MMM-\x1b[1m\033[37mMMM:\x1b[1m\033[32m\t\t",
	"\x1b[1m\033[37m  :MMM\x1b[1m\033[32m:MMM:`                `:MMM:\x1b[1m\033[37mMMM:\x1b[1m\033[32m\t",
	"\x1b[1m\033[37m   .MMM\x1b[1m\033[32m.MMMM:--------------:MMMM.\x1b[1m\033[37mMMM.\x1b[1m\033[32m\t\t",
	"\x1b[1m\033[37m     '-MMMM\x1b[1m\033[32m.-MMMMMMMMMMMMMMM-.\x1b[1m\033[37mMMMM-'\x1b[1m\033[32m\t\t",
	"\x1b[1m\033[37m       '.-MMMM\x1b[1m\033[32m``--:::::--``\x1b[1m\033[37mMMMM-.'\x1b[1m\033[32m\t\t",
	"\x1b[1m\033[37m            '-MMMMMMMMMMMMM-'\x1b[1m\033[32m\t\t",
	"\x1b[1m\033[37m               ``-:::::-``\x1b[1m\033[32m\t\t"
},
	*parrot[] = {
":oho/-`\t\t\t\t\t",
"`mMMMMMMMMMMMNmmdhy-\t\t\t",
" dMMMMMMMMMMMMMMMMMMs`\t\t\t",
" +MMsohNMMMMMMMMMMMMMm/\t\t\t",
" .My   .+dMMMMMMMMMMMMMh.\t\t",
"  +       :NMMMMMMMMMMMMNo\t\t",
"           `yMMMMMMMMMMMMMm:\t\t",
"             /NMMMMMMMMMMMMMy`\t\t",
"              .hMMMMMMMMMMMMMN+\t\t",
"                  ``-NMMMMMMMMMd-\t",
"                     /MMMMMMMMMMMs`\t",
"                      mMMMMMMMsyNMN/\t",
"                      +MMMMMMMo  :sNh.\t",
"                      `NMMMMMMm     -o/\t",
"                       oMMMMMMM.\t",
"                       `NMMMMMM+1\t",
"                        +MMd/NMh\t",
"                         mMm -mN`\t",
"                         /MM  `h:\t",
"                          dM`   .\t",
"                          :M-\t",
"                           d:\t",
"                           -+\t",
"                            -\t"
},
	*popOs[] = {
	"             /////////////\t\t\t",
	"         /////////////////////\t\t\t",
	"      ///////\x1b[1m\033[37m*767\x1b[1m\033[34m////////////////\t\t",
	"    //////\x1b[1m\033[37m7676767676*\x1b[1m\033[34m//////////////\t\t",
	"   /////\x1b[1m\033[37m76767\x1b[1m\033[34m//\x1b[1m\033[37m7676767\x1b[1m\033[34m//////////////\t\t",
	"  /////\x1b[1m\033[37m767676\x1b[1m\033[34m///\x1b[1m\033[37m*76767\x1b[1m\033[34m///////////////\t\t",
	" ///////\x1b[1m\033[37m767676\x1b[1m\033[34m///\x1b[1m\033[37m76767\x1b[1m\033[34m.///\x1b[1m\033[37m7676*\x1b[1m\033[34m///////\t\t",
	"/////////\x1b[1m\033[37m767676\x1b[1m\033[34m//\x1b[1m\033[37m76767\x1b[1m\033[34m///\x1b[1m\033[37m767676\x1b[1m\033[34m////////\t\t",
	"//////////\x1b[1m\033[37m76767676767\x1b[1m\033[34m////\x1b[1m\033[37m76767\x1b[1m\033[34m/////////\t\t",
	"///////////\x1b[1m\033[37m76767676\x1b[1m\033[34m//////\x1b[1m\033[37m7676\x1b[1m\033[34m//////////\t\t",
	"////////////,\x1b[1m\033[37m7676\x1b[1m\033[34m,///////\x1b[1m\033[37m767\x1b[1m\033[34m///////////\t\t",
	"/////////////*\x1b[1m\033[37m7676\x1b[1m\033[34m///////\x1b[1m\033[37m76\x1b[1m\033[34m////////////\t\t",
	"///////////////\x1b[1m\033[37m7676\x1b[1m\033[34m////////////////////\t\t",
	" ///////////////\x1b[1m\033[37m7676\x1b[1m\033[34m///\x1b[1m\033[37m767\x1b[1m\033[34m////////////\t\t",
	"  //////////////////////\x1b[1m\033[37m'\x1b[1m\033[34m////////////\t\t",
	"   //////\x1b[1m\033[37m.7676767676767676767,\x1b[1m\033[34m//////\t\t",
	"    /////\x1b[1m\033[37m767676767676767676767\x1b[1m\033[34m/////\t\t",
	"      ///////////////////////////\t\t",
	"         /////////////////////\t\t",
	"             /////////////\t\t"
},
	*ubuntu[] = {
	"            .-/+oossssoo+/-.\t\t\t",
	"        `:+ssssssssssssssssss+:`\t\t",
	"      -+ssssssssssssssssssyyssss+-\t\t",
	"    .ossssssssssssssssss\x1b[1m\033[37mdMMMNy\x1b[1m\033[31msssso.\t\t",
	"   /sssssssssss\x1b[1m\033[37mhdmmNNmmyNMMMMh\x1b[1m\033[31mssssss/\t\t",
	"  +sssssssss\x1b[1m\033[37mhm\x1b[1m\033[31myd\x1b[1m\033[37mMMMMMMMNddddy\x1b[1m\033[31mssssssss+\t\t",
	" /ssssssss\x1b[1m\033[37mhNMMM\x1b[1m\033[31myh\x1b[1m\033[37mhyyyyhmNMMMNh\x1b[1m\033[31mssssssss/\t\t",
	".ssssssss\x1b[1m\033[37mdMMMNh\x1b[1m\033[37mssssssssss\x1b[1m\033[37mhNMMMd\x1b[1m\033[31mssssssss.\t",
	"+ssss\x1b[1m\033[37mhhhyNMMNy\x1b[1m\033[31mssssssssssss\x1b[1m\033[37myNMMMy\x1b[1m\033[31msssssss+\t",
	"oss\x1b[1m\033[37myNMMMNyMMh\x1b[1m\033[31mssssssssssssss\x1b[1m\033[37mhmmmh\x1b[1m\033[31mssssssso\t",
	"oss\x1b[1m\033[37myNMMMNyMMh\x1b[1m\033[31msssssssssssssshmmmh\x1b[1m\033[31mssssssso\t",
	"+ssss\x1b[1m\033[37mhhhyNMMNy\x1b[1m\033[31mssssssssssss\x1b[1m\033[37myNMMMy\x1b[1m\033[31msssssss+\t",
	".ssssssss\x1b[1m\033[37mdMMMNh\x1b[1m\033[31mssssssssss\x1b[1m\033[37mhNMMMd\x1b[1m\033[31mssssssss.\t",
	" /ssssssss\x1b[1m\033[37mhNMMM\x1b[1m\033[31myh\x1b[1m\033[37mhyyyyhdNMMMNh\x1b[1m\033[31mssssssss/\t",
	"  +sssssssss\x1b[1m\033[37mdm\x1b[1m\033[31myd\x1b[1m\033[37mMMMMMMMMddddy\x1b[1m\033[31mssssssss+\t\t",
	"   /sssssssssss\x1b[1m\033[37mhdmNNNNmyNMMMMh\x1b[1m\033[31mssssss/\t\t",
	"    .ossssssssssssssssss\x1b[1m\033[37mdMMMNy\x1b[1m\033[31msssso.\t\t\t",
	"      -+sssssssssssssssss\x1b[1m\033[37myyy\x1b[1m\033[31mssss+-\t\t",
	"        `:+ssssssssssssssssss+:`\t\t\t",
	"            .-/+oossssoo+/-.\t\t\t"
};

#endif
