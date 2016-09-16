#include "../Header/StackAllocator.h"

StackAllocator::StackAllocator() {
	topPtr = nullptr;
	botPtr = nullptr;
}

StackAllocator::StackAllocator(unsigned int byteSize) {
	StackAllocator();
}

StackAllocator::~StackAllocator() {

}

void* StackAllocator::Alloc(unsigned int byteSize) {

};

void StackAllocator::ClearStack() {

};

void StackAllocator::FreeToMarker(){

};

StackAllocator::Marker StackAllocator::GetMarker(){

};
