#pragma once
#include "MessageTypes.h"
#include "cVariant.h"
#include <assert.h>
namespace Messaging {
	struct Message {
		Message(MessageTypes type) {

		}

		virtual ~Message() {

		}

		MessageTypes type;
	};

	template <typename MsgType>
	inline MsgType* ConvertMessageTo(Message* msg) {
#ifdef _DEBUG
		//dynamic_cast를 이용하여 런타임 타입 검사 수행.
		MsgType* downcasted = dynamic_cast<MsgType*>(msg);
		assert(downcasted && "잘못된 Downcasting입니다.");
#elif
		//릴리즈에서는 느린? dynamic_cast대신 RTTI 체크가 없는 static_cast를 이용
		//대신 잘못된 형변환에 대한 오류는 찾을 수 없다.
		MsgType* downcasted = static_cast<MsgType*>(msg);
#endif
		return downcasted;
	}

}