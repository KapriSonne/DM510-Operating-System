#include "linux/kernel.h"
#include "linux/unistd.h"
#include "linux/slab.h"
#include "linux/uaccess.h"


#define LOCKED 1
#define NOT_FOUND 404
#define LOCK(f) { \
	if(lock) return LOCKED; \
	else lock = 1;\
	f \
	lock = 0;\
}while(false) \


typedef struct msg_t{
	void * message;
	int length;
	struct msg_t * next;
}msg_t;

msg_t * stack_push(msg_t * stack_top,void * message, int length){
	msg_t * new_msg = kmalloc(sizeof(*new_msg), GFP_KERNEL);
	new_msg -> message = kmalloc(length * sizeof(*message),GFP_KERNEL);
	new_msg -> length = length;
	new_msg -> next = stack_top;
	return new_msg;
}

msg_t * stack_pop(msg_t * stack_top){
	msg_t * next = stack_top->next;
	kfree(stack_top->message);
	kfree(stack_top);
	return next;
}

static msg_t * top = NULL;
int lock = 0;

int sys_get(void * message, int length){
	if(NULL == top) return NOT_FOUND;
	LOCK(
		printk("Pop message\n");
		const int min = length < top->length ? length : top->length;
		copy_to_user(message,top->message,min );
		top = stack_pop(top);
	);
	return 0;
}
int sys_put(void * message, int length){
	LOCK(
		printk("Push message\n");
		top = stack_push(top, message, length);
		copy_from_user(top->message, message, length);
	);
	return 0;
}
int sys_length(int *length){
	if(NULL == top) return NOT_FOUND;
	LOCK(
		copy_to_user(length,&(top->length),sizeof(*length));
	);
	return 0;
}
