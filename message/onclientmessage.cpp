#include "head.pb.h"
#include "suoha.pb.h"
#include "gameroot.h"
#include "utils/tarslog.h"
#include "common/macros.h"
#include "message/onclientmessage.h"
#include "logic/clientlogic/head.h"

namespace game
{
    namespace message
    {
        void onClientMessage(long uid, int eMSG, const vector<char> &vecMsgData, GameRoot *root)
        {
            using namespace logic;

            try
            {
                switch(static_cast<unsigned char>(eMSG))
                {
                //下注请求及应答
                case XGameSHProto::SH_msg2csTokenBet_E:
                {
                    clientlogic::TokenBet(uid, vecMsgData, root);
                }
                break;
                case XGameSHProto::SH_msg2csGameStation_E:
                {
                    clientlogic::GameStation(uid, vecMsgData, root);
                }
                break;
                case XGameSHProto::SH_msg2cDebugCard_E:
                {
                    clientlogic::DebugCards(uid, vecMsgData, root);
                }
                break;
                case XGameSHProto::SH_msg2csBuBi_E:
                {
                    clientlogic::BuBi(uid, vecMsgData, root);
                }
                break;
                case XGameSHProto::SH_msg2sCheckBegin_E:
                {
                    clientlogic::TestBegin(uid, vecMsgData, root);
                }
                break;
                //
                default:
                {
                    LOG_ERROR("undefined network message from remote user, uid : " << uid << ", eMSG: " << eMSG);
                }
                break;
                }
            }
            catch (const TarsDecodeException &e)
            {
                ERROR(string("catch tars decode exception : ") + e.what());
            }
            catch (const TarsEncodeException &e)
            {
                ERROR(string("catch tars encode exception : ") + e.what());
            }
            catch (const TarsProtoException &e)
            {
                ERROR(string("catch proto exception : ") + e.what());
            }
            catch (const TC_Exception &e)
            {
                ERROR(string("catch tc exception : ") + e.what());
            }
            catch (const std::exception &e)
            {
                ERROR(string("catch std exception : ") + e.what());
            }
            catch (...)
            {
                ERROR("catch unknown exception.");
            }
        }
    };
};


