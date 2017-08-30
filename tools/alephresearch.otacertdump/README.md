**otacertdump**

By Roee Hay / Aleph Research, HCL Technologies

Takes a signed Android OTA, and dumps the certificate information.

Ripped from:

[/AOSP/frameworks/base/core/java/android/os/RecoverySystem.java](https://android.googlesource.com/platform/frameworks/base/+/android-7.1.2_r11/core/java/android/os/RecoverySystem.java)

For example:

```terminal 
$ gradlew build
[...]
$ java -cp alephresearch.otacertdump\build\libs\alephresearch.otacertdump.jar alephresearch.otacertdump.OTACertDump marlin-ota-nhg47l-1b06c596.zip
[
[
  Version: V3
  Subject: CN=Android, OU=Android, O=Google Inc., L=Mountain View, ST=California, C=US
  Signature Algorithm: SHA256withRSA, OID = 1.2.840.113549.1.1.11

  Key:  Sun RSA public key, 2048 bits
  modulus: 25592937703804963478344235585058338178048398896105388884717942715556557489140899506551826349704980680779732369468301563840213756446550158745527437619118616591670860003274171116607728844156911786698766633115375778414006148464561264319524650316558392440063679684050274139405365287339797176796643240388346389863965369531551836562364578357473930058855152929046762965928513777441872678889707180408511911350764185465755501360816569816656415532759407303379391483919465769268197813531101074307700555929513299466550567501335406057472792274164890951756065516855222638933807376590351544936112044544752101748918282935478123707503
  public exponent: 65537
  Validity: [From: Tue May 10 21:13:28 IDT 2016,
               To: Sat Sep 26 21:13:28 IDT 2043]
  Issuer: CN=Android, OU=Android, O=Google Inc., L=Mountain View, ST=California, C=US
  SerialNumber: [    ef1a5768 250ee502]

Certificate Extensions: 3
[1]: ObjectId: 2.5.29.35 Criticality=false
AuthorityKeyIdentifier [
KeyIdentifier [
0000: F3 21 5D 27 6A B6 BF 3A   CF EF 06 8F 1E 07 BF B6  .!]'j..:........
0010: 48 5A 1B 87                                        HZ..
]
]

[2]: ObjectId: 2.5.29.19 Criticality=false
BasicConstraints:[
  CA:true
  PathLen:2147483647
]

[3]: ObjectId: 2.5.29.14 Criticality=false
SubjectKeyIdentifier [
KeyIdentifier [
0000: F3 21 5D 27 6A B6 BF 3A   CF EF 06 8F 1E 07 BF B6  .!]'j..:........
0010: 48 5A 1B 87                                        HZ..
]
]

]
  Algorithm: [SHA256withRSA]
  Signature:
0000: 01 65 98 28 B6 9C B0 4E   D5 2A 44 5F E5 6C D0 AC  .e.(...N.*D_.l..
0010: 15 B9 48 21 6A 48 09 66   7F 0D 0C 73 45 ED 57 7C  ..H!jH.f...sE.W.
0020: 86 71 4E E5 9C 3F 39 65   C6 EC 2A 2A 2F 6F B2 60  .qN..?9e..**/o.`
0030: 42 22 5F B1 7B 2B 49 2E   39 11 B6 63 14 A8 A8 EC  B"_..+I.9..c....
0040: F7 E9 9A EB 67 0C CA 3E   FB 04 67 E3 E5 6B F3 C7  ....g..>..g..k..
0050: 35 42 23 B9 EB 1A F5 C6   D9 3B C3 88 E6 4B DF 93  5B#......;...K..
0060: 27 ED AA 85 EE D5 B4 66   F2 CA EA F1 FC D6 DE 9E  '......f........
0070: CD 2C 9E 9B 58 FC 0E E2   FA B0 D1 AE 13 31 8F A6  .,..X........1..
0080: 38 89 6B 67 EB FE CB D0   2C 60 64 C4 7E D8 90 8E  8.kg....,`d.....
0090: 1A AB 11 BB 7D FD 99 D2   BB 50 AA BE 30 59 3B F5  .........P..0Y;.
00A0: E1 FE 77 E5 D7 C9 AA 90   4B AC BE 91 17 35 E9 AA  ..w.....K....5..
00B0: 42 AE 6F BB D0 F4 AE 07   AF E7 7B EB BB 99 B3 B4  B.o.............
00C0: 28 72 F8 B0 3C 97 7E 63   4C AE F3 28 0C 57 6C 64  (r..<..cL..(.Wld
00D0: C0 A9 DF D2 5B 6A 8B A4   4A CA 3B 28 C6 3B BD 65  ....[j..J.;(.;.e
00E0: 07 E5 1C E4 DF 99 CB C2   9E C4 12 B5 B2 FF 66 75  ..............fu
00F0: C6 E3 3A AD 5B 4D BE 68   83 19 C0 2C 95 85 21 7C  ..:.[M.h...,..!.

]
```                                                                                                                                                                                  ```
