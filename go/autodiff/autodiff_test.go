package autodiff

import (
	"fmt"
	"testing"
)

func TestIdentity(t *testing.T) {
	t1 := NewTensor(1, nil)
	t2 := t1.Add(t1)
	fmt.Println(t2.Data)
}
