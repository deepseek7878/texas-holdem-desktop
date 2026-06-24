#pragma once

#include "common/macros.h"
#include "gameroot.h"
#include "gameserver.h"
#include "dz.pb.h"

namespace game
{
    namespace message
    {
        int sendClientMessage(const long &pid, int eMSG, const std::vector<char> &vecData, GameRoot *root);
        int sendClientMessage(const long &pid, vector<int> &eMSG, const std::vector<vector<char> > &vecData, GameRoot *root);

        int sendAllClientMessage(int eMSG, const std::vector<char> &vecData, GameRoot *root);
        int sendAllClientMessage(vector<int> &eMSG, const std::vector<vector<char> > &vecData, GameRoot *root);

        int sendClientWatchGameData(int eMSG, const std::vector<char> &vecData, GameRoot *root);
        int sendClientWatchGameData(vector<int> &eMSG, const std::vector<vector<char> > &vecData, GameRoot *root);

        template<class T>
        int sendClientMessage(const long &uid, int eMSG, T const &TMsg, GameRoot *root)
        {
            return sendClientMessage(uid, eMSG, pbTobuffer(TMsg), root);
        }

        template<class T>
        int sendAllClientMessage(int eMSG, T const &TMsg, GameRoot *root)
        {
            return sendAllClientMessage(eMSG, pbTobuffer(TMsg), root);
        }

        template<class T>
        int sendClientWatchGameData(int eMSG, T const &TMsg, GameRoot *root)
        {
            return sendClientWatchGameData(eMSG, pbTobuffer(TMsg), root);
        }
    };
};

