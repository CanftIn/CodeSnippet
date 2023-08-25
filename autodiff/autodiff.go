package autodiff

type Op interface {
	forward(from_tensors []*Tensor) *Tensor
	backward(from_tensors []*Tensor, grad float64) []float64
}

type Tensor struct {
	Data        float64   // 数据
	FromTensors []*Tensor // 从哪个Tensor计算得到的，用于反向传播
	Grad        float64   // 梯度
}

type AddOp struct {
	Op // 操作
}

type SubOp struct {
	Op
}

type MulOp struct {
	Op
}

type MulWithMatrixOp struct {
	Op
}

type DivOp struct {
	Op
}

type SumOp struct {
	Op
}

type ExpOp struct {
	Op
}

type LogOp struct {
	Op
}

func (op *AddOp) forward(from_tensors []*Tensor) *Tensor {
	tensor := &Tensor{
		Data:        from_tensors[0].Data + from_tensors[1].Data,
		FromTensors: from_tensors,
	}
	return tensor
}

func (op *AddOp) backward(from_tensors []*Tensor, grad float64) []float64 {
	return []float64{grad, grad}
}

func (op *SubOp) forward(from_tensors []*Tensor) *Tensor {
	tensor := &Tensor{
		Data:        from_tensors[0].Data - from_tensors[1].Data,
		FromTensors: from_tensors,
	}
	return tensor
}

func (op *SubOp) backward(from_tensors []*Tensor, grad float64) []float64 {
	return []float64{grad, -grad}
}

func (op *MulOp) forward(from_tensors []*Tensor) *Tensor {
	tensor := &Tensor{
		Data:        from_tensors[0].Data * from_tensors[1].Data,
		FromTensors: from_tensors,
	}
	return tensor
}

func (op *MulOp) backward(from_tensors []*Tensor, grad float64) []float64 {
	return []float64{grad * from_tensors[1].Data, grad * from_tensors[0].Data}
}

// TODO: Fix this
func (op *MulWithMatrixOp) forward(from_tensors []*Tensor) *Tensor {
	tensor := &Tensor{
		Data:        from_tensors[0].Data * from_tensors[1].Data,
		FromTensors: from_tensors,
	}
	return tensor
}

func (op *MulWithMatrixOp) backward(from_tensors []*Tensor, grad float64) []float64 {
	return []float64{grad * from_tensors[1].Data, grad * from_tensors[0].Data}
}

func (op *DivOp) forward(from_tensors []*Tensor) *Tensor {
	tensor := &Tensor{
		Data:        from_tensors[0].Data / from_tensors[1].Data,
		FromTensors: from_tensors,
	}
	return tensor
}

func (op *DivOp) backward(from_tensors []*Tensor, grad float64) []float64 {
	return []float64{grad / from_tensors[1].Data, -grad * from_tensors[0].Data / (from_tensors[1].Data * from_tensors[1].Data)}
}

func (op *SumOp) forward(from_tensors []*Tensor) *Tensor {
	tensor := &Tensor{
		Data:        from_tensors[0].Data + from_tensors[1].Data,
		FromTensors: from_tensors,
	}
	return tensor
}

func (op *SumOp) backward(from_tensors []*Tensor, grad float64) []float64 {
	return []float64{grad, grad}
}

func NewTensor(data float64, from_tensors []*Tensor) *Tensor {
	t := &Tensor{
		Data:        data,
		FromTensors: from_tensors,
	}
	return t
}

func (t *Tensor) Add(t2 *Tensor) *Tensor {
	op := &AddOp{}
	t3 := op.forward([]*Tensor{t, t2})
	t3.FromTensors = []*Tensor{t, t2}
	return t3
}

func (t *Tensor) backward(grad float64) {
	if grad == 
}
