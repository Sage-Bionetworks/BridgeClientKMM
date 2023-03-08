package org.sagebionetworks.bridge.assessmentmodel.upload

import android.content.Context
import android.content.res.AssetManager
import co.touchlab.kermit.Logger
import org.sagebionetworks.bridge.data.AndroidStudyUploadEncryptor
import org.spongycastle.cms.CMSException
import org.spongycastle.jcajce.provider.asymmetric.x509.CertificateFactory
import java.io.IOException
import java.io.OutputStream
import java.security.cert.CertificateException
import java.security.cert.X509Certificate

// Encryptor interface so tests can implement a version that doesn't do encryption
interface AndroidUploadEncryptor {

    @Throws(CMSException::class, IOException::class)
    fun encrypt(stream: OutputStream): OutputStream
}

// Wrapper for AndroidStudyUploadEncryptor which is in a library we haven't had to change in years
class AndroidStudyUploadEncryptorWrapper (val context: Context) : AndroidUploadEncryptor {

    val STUDY_PUBLIC_KEY = "study_public_key.pem"

    private val encryptor = AndroidStudyUploadEncryptor(getPublicKey())

    @Throws(IOException::class, CertificateException::class)
    fun getPublicKey(): X509Certificate {
        try {
            context.assets.open(
                STUDY_PUBLIC_KEY,
                AssetManager.ACCESS_BUFFER
            ).use { publicKeyFile ->
                return CertificateFactory()
                    .engineGenerateCertificate(
                        publicKeyFile
                    ) as X509Certificate
            }
        } catch (e: IOException) {
            Logger.e("Could not load public key from /assets/study_public_key.pem", e)
            throw e
        }
    }

    @Throws(CMSException::class, IOException::class)
    override fun encrypt(stream: OutputStream): OutputStream {
        return encryptor.encrypt(stream)
    }

}