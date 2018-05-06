// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

//
// Main network
//

// Convert the pnSeeds array into usable address objects.
static void convertSeeds(std::vector<CAddress> &vSeedsOut, const unsigned int *data, unsigned int count, int port)
{
     // It'll only connect to one or two seed nodes because once it connects,
     // it'll get a pile of addresses with newer timestamps.
     // Seed nodes are given a random 'last seen time' of between one and two
     // weeks ago.
     const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int k = 0; k < count; ++k)
    {
        struct in_addr ip;
        unsigned int i = data[k], t;
        
        // -- convert to big endian
        t =   (i & 0x000000ff) << 24u
            | (i & 0x0000ff00) << 8u
            | (i & 0x00ff0000) >> 8u
            | (i & 0xff000000) >> 24u;
        
        memcpy(&ip, &t, sizeof(ip));
        
        CAddress addr(CService(ip, port));
        addr.nTime = GetTime()-GetRand(nOneWeek)-nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x12;
        pchMessageStart[1] = 0x13;
        pchMessageStart[2] = 0x14;
        pchMessageStart[3] = 0x1e;
        vAlertPubKey = ParseHex("0323740193a8560083f057e3bf354ce8b5739d4242cd9992d1fb95ebe9d0c626cd");
        nDefaultPort = 51471;
        nRPCPort = 51472;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        //bnProofOfWorkLimit = CBigNum(~uint256(0) >> 20);

        // Build the genesis block. Note that the output of the genesis coinbase cannot
        // be spent as it did not originally exist in the database.
        //
        //CBlock(hash=000001faef25dec4fbcf906e6242621df2c183bf232f263d0ba5b101911e4563, ver=1, hashPrevBlock=0000000000000000000000000000000000000000000000000000000000000000, hashMerkleRoot=12630d16a97f24b287c8c2594dda5fb98c9e6c70fc61d44191931ea2aa08dc90, nTime=1393221600, nBits=1e0fffff, nNonce=164482, vtx=1, vchBlockSig=)
        //  Coinbase(hash=12630d16a9, nTime=1393221600, ver=1, vin.size=1, vout.size=1, nLockTime=0)
        //    CTxIn(COutPoint(0000000000, 4294967295), coinbase 00012a24323020466562203230313420426974636f696e2041544d7320636f6d6520746f20555341)
        //    CTxOut(empty)
        //  vMerkleTree: 12630d16a9
        const char* pszTimestamp = "07 April 2018.";


        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].SetEmpty();
        CTransaction txNew(1, 1523170800, vin, vout, 0);
       
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1523170800;
        //genesis.nBits    = 0x1e0fffff;
        genesis.nBits    = 0x1f00ffff;
        genesis.nNonce   = 82428;

        hashGenesisBlock = genesis.GetHash();

        assert(hashGenesisBlock == uint256("0x0000e85047284be84a0da3d75d31cfc7e5a6a408eb4713459ad59d0ddf592923"));
        assert(genesis.hashMerkleRoot == uint256("0x87ebe5b45fe7eb9372a723939fb6e36fc8ccba0a5939b15c2f4a14efc8e9e4a2"));
        
        /*uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
        uint256 thash;
        unsigned int profile = 0x0;

        while(true){
            neoscrypt((unsigned char *) &genesis.nVersion, (unsigned char *) &thash, profile);
            if (thash <= hashTarget) break;

            if ((genesis.nNonce & 0xFFF) == 0){
                printf("nonce %08X: hash = %s (target = %s)\n", genesis.nNonce, thash.ToString().c_str(), hashTarget.ToString().c_str());}

            ++genesis.nNonce;
            if (genesis.nNonce == 0){
            printf("NONCE WRAPPED, incrementing time\n");
            ++genesis.nTime;}
        }

        printf("genesis.nTime = %u \n", genesis.nTime);
        printf("genesis.nNonce = %u \n", genesis.nNonce);
        printf("genesis.GetHash = %s\n", genesis.GetHash().ToString().c_str());
        printf("genesis.hashMerkleRoot = %s\n", genesis.hashMerkleRoot.ToString().c_str());*/
        
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,25);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,85);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,153);
        base58Prefixes[STEALTH_ADDRESS] = std::vector<unsigned char>(1,40);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

        vSeeds.push_back(CDNSSeedData("0","dns0.bytepay.org"));
        vSeeds.push_back(CDNSSeedData("1","dns1.bytepay.org"));
        vSeeds.push_back(CDNSSeedData("2","dns2.bytepay.org"));
        vSeeds.push_back(CDNSSeedData("3","dns3.bytepay.org"));
        vSeeds.push_back(CDNSSeedData("4","dns4.bytepay.org"));
        vSeeds.push_back(CDNSSeedData("5","dns5.bytepay.org"));
        vSeeds.push_back(CDNSSeedData("6","dns6.bytepay.org"));
        vSeeds.push_back(CDNSSeedData("7","dns7.bytepay.org"));
        vSeeds.push_back(CDNSSeedData("8","dns8.bytepay.org"));
        vSeeds.push_back(CDNSSeedData("9","dns9.bytepay.org"));

        convertSeeds(vFixedSeeds, pnSeed, ARRAYLEN(pnSeed), nDefaultPort);

        nPoolMaxTransactions = 3;
        strDarksendPoolDummyAddress = "BG7PTjkwkjbmB4wMvYiYgMjWDiCBApudM8";
        nLastPOWBlock = 21000;
        nPOSStartBlock = 21000;
        //nMasternodePaymentStartBlock = 1;
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet
//

class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x12;
        pchMessageStart[1] = 0x13;
        pchMessageStart[2] = 0x14;
        pchMessageStart[3] = 0x1f;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        vAlertPubKey = ParseHex("0323740193a8560083f057e3bf354ce8b5739d4242cd9992d1fb95ebe9d0c626cd");
        nDefaultPort = 61471;
        nRPCPort = 61472;
        strDataDir = "testnet";

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,153);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196);
        base58Prefixes[SECRET_KEY]     = std::vector<unsigned char>(1,239);
        base58Prefixes[STEALTH_ADDRESS] = std::vector<unsigned char>(1,40);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();

        convertSeeds(vFixedSeeds, pnTestnetSeed, ARRAYLEN(pnTestnetSeed), nDefaultPort);

        nLastPOWBlock = 0x7fffffff;
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    
    bool fTestNet = GetBoolArg("-testnet", false);
    
    if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
