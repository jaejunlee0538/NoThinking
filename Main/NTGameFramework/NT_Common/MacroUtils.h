#pragma once

#define SAFE_RELEASE(p) if(p){p->Release(); p = NULL;}
#define SAFE_RELEASE_ARR(pArr, count) \
					if(pArr){\
						for(int i=0;i<count;++i){\
							if (pArr[i]) {\
								pArr[i]->Release();\
								pArr[i] = NULL;\
							}\
						}\
					}

#define SAFE_DELETE(p) if(p){delete p; p = NULL;}
#define SAFE_DELETE_ARR(pArr) if(pArr){delete[] pArr; pArr = NULL;}

///////////////////////////////////////////////////////////////////////
//GETTER/SETTER�� ����/���Ǹ� ������ִ� ��ũ�� ����
//��� ������ decltype�� ���� ��ȯ���� �Ű������� �ڷ����� �߷��ϱ� ������
//��� ������ �ݵ�� �Ʒ� ��ũ�κ��� ���� ����Ǿ� �־�� �Ѵ�.
#define MAKE_GETSETTER(member, fncSuffix) \
decltype(member) Get##fncSuffix() const{ return member; }\
void Set##fncSuffix(decltype(member) value){member = value;}

#define MAKE_GETSETTER_REF(member, fncSuffix)\
const decltype(member)& Get##fncSuffix() const{ return member; }\
void Set##fncSuffix(const decltype(member)& value){member = value;}

#define MAKE_GETTER(member, fncSuffix) \
decltype(member) Get##fncSuffix() const { return member; }

#define MAKE_GETTER_REF(member, fncSuffix) \
const decltype(member)& Get##fncSuffix() const { return member; }

#define MAKE_SETTER(member, fncSuffix) \
void Set##fncSuffix(decltype(member) value){member = value;}

#define MAKE_SETTER_REF(member, fncSuffix)\
void Set##fncSuffix(const decltype(member)& value){member = value;}

#define MAKE_SETTER_CODE(member, fncSuffix, codeAfterSet) \
void Set##fncSuffix(decltype(member) value){member = value;codeAfterSet;}

#define MAKE_SETTER_REF_CODE(member, fncSuffix, codeAfterSet)\
void Set##fncSuffix(const decltype(member)& value){member = value;codeAfterSet;}