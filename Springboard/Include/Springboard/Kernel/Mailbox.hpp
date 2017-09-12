#pragma once

#include <Springboard/Common.hpp>
#include <ch.h>

namespace Springboard {
namespace Kernel {

template <typename T, int Size>
class Mailbox
{
public:
    Mailbox()
    {
        chMBObjectInit(&mMailbox, mData, Size);
    }

    inline void Reset()
    {
        chMBReset(&mMailbox);
    }

    inline void ResetI()
    {
        chMBResetI(&mMailbox);
    }

    inline void Resume()
    {
        chMBResumeX(&mMailbox);
    }

    inline void Post(T& data)
    {
        msg_t result = chMBPost(&mMailbox, (msg_t)&data, TIME_INFINITE);
        ASSERT(result == MSG_OK);
    }

    inline void PostI(T& data)
    {
        msg_t result = chMBPostI(&mMailbox, (msg_t)&data);
        ASSERT(result == MSG_OK);
    }

    inline void PostAhead(T& data)
    {
        msg_t result = chMBPostAhead(&mMailbox, (msg_t)&data, TIME_INFINITE);
        ASSERT(result == MSG_OK);
    }

    inline void PostAheadI(T& data)
    {
        msg_t result = chMBPostAheadI(&mMailbox, (msg_t)&data);
        ASSERT(result == MSG_OK);
    }

    inline T& Fetch()
    {
        msg_t data = 0;
        msg_t result = chMBFetch(&mMailbox, &data, TIME_INFINITE);
        ASSERT(result == MSG_OK);
        return *((T*)data);
    }

    inline T& FetchI()
    {
        msg_t data = 0;
        msg_t result = chMBFetchI(&mMailbox, &data);
        ASSERT(result == MSG_OK);
        return *((T*)data);
    }

private:
    mailbox_t mMailbox;
    msg_t mData[Size];
};

}
}
