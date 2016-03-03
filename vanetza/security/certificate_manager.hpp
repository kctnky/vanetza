#ifndef CERTIFICATE_MANAGER_HPP
#define CERTIFICATE_MANAGER_HPP

#include <vanetza/common/clock.hpp>
#include <vanetza/security/backend_cryptopp.hpp>
#include <vanetza/security/basic_elements.hpp>
#include <vanetza/security/certificate.hpp>
#include <vanetza/security/ecdsa256.hpp>

namespace vanetza
{
namespace security
{

/**
 * \brief A Manager to handle Certificates using Crypto++
 * \todo rename to CryptoPPCertManager
 * \todo create a base class
 */
class CertificateManager
{
public:
    CertificateManager(const Clock::time_point& time_now);

    /**
     * \brief generate a certificate
     *
     * \param key_pair keys used to create the certificate
     * \return generated certificate
     */
    Certificate generate_certificate(const ecdsa256::KeyPair& key_pair);

    /**
     * \brief check certificate
     * \param certificate to verify
     * \return certificate status
     */
    CertificateValidity check_certificate(const Certificate& certificate);

    /**
     * \brief get own certificate for signing
     * \return own certificate
     */
    const Certificate& own_certificate();

    /**
     * \brief get own private key
     * \return private key
     */
    const ecdsa256::PrivateKey& own_private_key();

private:
    /** \brief retrieve common root key pair (for all instances)
     *
     * \note This is only a temporary workaround!
     * \return root key pair
     */
    const ecdsa256::KeyPair& get_root_key_pair();

    BackendCryptoPP m_crypto_backend;
    const Clock::time_point& m_time_now;
    const ecdsa256::KeyPair& m_root_key_pair;
    HashedId8 m_root_certificate_hash;
    ecdsa256::KeyPair m_own_key_pair;
    Certificate m_own_certificate;
};

} // namespace security
} // namespace vanetza

#endif // CERTIFICATE_MANAGER_HPP
