#include <vector>
#include "Pipeline.h"

Pipeline & Pipeline::AddStage(PipelineStage *_pStage) {
	_stages.push_back(_pStage);
	return *this;
}

void Pipeline::Start() {
	for (auto &s : _stages) {
		s->Execute(_pCtx);
	}
}