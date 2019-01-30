(* My first theorem *)

Definition pierce := forall (p q : Prop),
  ((p -> q) -> p) -> p.
Definition lem := forall p, p \/ ~ p.

Theorem pierce_equiv_lem: pierce <-> lem.
Proof.
  unfold pierce, lem.
  firstorder.