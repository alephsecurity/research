/*
    Roee Hay / Aleph Research, HCL Technologies

    Takes a signed Android OTA, and prints the certificate information

    ripped from:
    /AOSP/frameworks/base/core/java/android/os/RecoverySystem.java

*/

package alephresearch.otacertdump;

import java.io.ByteArrayInputStream;
import java.io.File;
import java.io.IOException;
import java.io.RandomAccessFile;
import java.security.SignatureException;
import java.security.cert.X509Certificate;

import sun.security.pkcs.PKCS7;

public class OTACertDump {

    public static void main(String[] args) throws SignatureException, IOException {

        if (args.length < 1)
        {
            System.out.println("Where is the input?");
            return;
        }

        File packageFile = new File(args[0]);
        final long fileLen = packageFile.length();
        final RandomAccessFile raf = new RandomAccessFile(packageFile, "r");
        try {
            final long startTimeMillis = System.currentTimeMillis();

            raf.seek(fileLen - 6);
            byte[] footer = new byte[6];
            raf.readFully(footer);

            if (footer[2] != (byte)0xff || footer[3] != (byte)0xff) {
                throw new SignatureException("no signature in file (no footer)");
            }

            final int commentSize = (footer[4] & 0xff) | ((footer[5] & 0xff) << 8);
            final int signatureStart = (footer[0] & 0xff) | ((footer[1] & 0xff) << 8);

            byte[] eocd = new byte[commentSize + 22];
            raf.seek(fileLen - (commentSize + 22));
            raf.readFully(eocd);

            // Check that we have found the start of the
            // end-of-central-directory record.
            if (eocd[0] != (byte)0x50 || eocd[1] != (byte)0x4b ||
                    eocd[2] != (byte)0x05 || eocd[3] != (byte)0x06) {
                throw new SignatureException("no signature in file (bad footer)");
            }

            for (int i = 4; i < eocd.length-3; ++i) {
                if (eocd[i  ] == (byte)0x50 && eocd[i+1] == (byte)0x4b &&
                        eocd[i+2] == (byte)0x05 && eocd[i+3] == (byte)0x06) {
                    throw new SignatureException("EOCD marker found after start of EOCD");
                }
            }

            // Parse the signature
            PKCS7 block =
                    new PKCS7(new ByteArrayInputStream(eocd, commentSize+22-signatureStart, signatureStart));

            // Take the first certificate from the signature (packages
            // should contain only one).
            X509Certificate[] certificates = block.getCertificates();
            if (certificates == null || certificates.length == 0) {
                throw new SignatureException("signature contains no certificates");
            }
            X509Certificate cert = certificates[0];

            System.out.println(cert);


        } finally {
            raf.close();
        }
    }

}
