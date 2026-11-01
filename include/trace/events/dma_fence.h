#undef TRACE_SYSTEM
#define TRACE_SYSTEM dma_fence

#if !defined(_TRACE_DMA_FENCE_H) || defined(TRACE_HEADER_MULTI_READ)
#define _TRACE_DMA_FENCE_H

#include <linux/tracepoint.h>

struct dma_fence;

TRACE_EVENT(dma_fence_annotate_wait_on,

	/* dma_fence: the dma_fence waiting on f1, f1: the dma_fence to be waited on. */
	TP_PROTO(struct dma_fence *dma_fence, struct dma_fence *f1),

	TP_ARGS(dma_fence, f1),

	TP_STRUCT__entry(
		__string(driver, dma_fence->ops->get_driver_name(dma_fence))
		__string(timeline, dma_fence->ops->get_timeline_name(dma_fence))
		__field(unsigned int, context)
		__field(unsigned int, seqno)

		__string(waiting_driver, f1->ops->get_driver_name(f1))
		__string(waiting_timeline, f1->ops->get_timeline_name(f1))
		__field(unsigned int, waiting_context)
		__field(unsigned int, waiting_seqno)
	),

	TP_fast_assign(
		__assign_str(driver, dma_fence->ops->get_driver_name(dma_fence))
		__assign_str(timeline, dma_fence->ops->get_timeline_name(dma_fence))
		__entry->context = dma_fence->context;
		__entry->seqno = dma_fence->seqno;

		__assign_str(waiting_driver, f1->ops->get_driver_name(f1))
		__assign_str(waiting_timeline, f1->ops->get_timeline_name(f1))
		__entry->waiting_context = f1->context;
		__entry->waiting_seqno = f1->seqno;

	),

	TP_printk("driver=%s timeline=%s context=%u seqno=%u "	\
		  "waits on driver=%s timeline=%s context=%u seqno=%u",
		  __get_str(driver), __get_str(timeline), __entry->context,
		  __entry->seqno,
		  __get_str(waiting_driver), __get_str(waiting_timeline),
		  __entry->waiting_context, __entry->waiting_seqno)
);

DECLARE_EVENT_CLASS(dma_fence,

	TP_PROTO(struct dma_fence *dma_fence),

	TP_ARGS(dma_fence),

	TP_STRUCT__entry(
		__string(driver, dma_fence->ops->get_driver_name(dma_fence))
		__string(timeline, dma_fence->ops->get_timeline_name(dma_fence))
		__field(unsigned int, context)
		__field(unsigned int, seqno)
	),

	TP_fast_assign(
		__assign_str(driver, dma_fence->ops->get_driver_name(dma_fence))
		__assign_str(timeline, dma_fence->ops->get_timeline_name(dma_fence))
		__entry->context = dma_fence->context;
		__entry->seqno = dma_fence->seqno;
	),

	TP_printk("driver=%s timeline=%s context=%u seqno=%u",
		  __get_str(driver), __get_str(timeline), __entry->context,
		  __entry->seqno)
);

DEFINE_EVENT(dma_fence, dma_fence_emit,

	TP_PROTO(struct dma_fence *dma_fence),

	TP_ARGS(dma_fence)
);

DEFINE_EVENT(dma_fence, dma_fence_init,

	TP_PROTO(struct dma_fence *dma_fence),

	TP_ARGS(dma_fence)
);

DEFINE_EVENT(dma_fence, dma_fence_destroy,

	TP_PROTO(struct dma_fence *dma_fence),

	TP_ARGS(dma_fence)
);

DEFINE_EVENT(dma_fence, dma_fence_enable_signal,

	TP_PROTO(struct dma_fence *dma_fence),

	TP_ARGS(dma_fence)
);

DEFINE_EVENT(dma_fence, dma_fence_signaled,

	TP_PROTO(struct dma_fence *dma_fence),

	TP_ARGS(dma_fence)
);

DEFINE_EVENT(dma_fence, dma_fence_wait_start,

	TP_PROTO(struct dma_fence *dma_fence),

	TP_ARGS(dma_fence)
);

DEFINE_EVENT(dma_fence, dma_fence_wait_end,

	TP_PROTO(struct dma_fence *dma_fence),

	TP_ARGS(dma_fence)
);

#endif /*  _TRACE_DMA_FENCE_H */

/* This part must be outside protection */
#include <trace/define_trace.h>
