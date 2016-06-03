#pragma once

extern "C"
{
extern gboolean mono_object_is_alive(MonoObject* obj);

#include <glib.h>
#include <mono/metadata/object.h>
}

#include <cstdint>
#include <list>

struct _MonoClass;
struct StackFrame;

struct OutfileWriter;
struct BackTrace;
struct BackTraceByClass;

struct LiveObject
{
	MonoObject* obj;
	uint32_t size;
	uint32_t age;
	uint32_t largest_size;
};

struct Accountant
{
	_MonoClass* klass;
	BackTraceByClass* backtrace;
	gboolean dirty;

	guint32   n_allocated_objects;
	guint64   n_allocated_bytes;
	guint32   allocated_total_age;
	guint32   allocated_total_weight;
	guint32   n_live_objects;
	guint32   n_live_bytes;
	guint32   live_total_age;
	guint32   live_total_weight;

	std::list<LiveObject> live_objects;

	Accountant();
	~Accountant();

private:
	void update_for_resize(LiveObject& live, uint32_t new_size);
public:
	void register_object(MonoObject* obj, uint32_t obj_size);
	void post_gc_processing(OutfileWriter* ofw);
};

Accountant* accountant_new(_MonoClass* klass, BackTraceByClass* backtrace);