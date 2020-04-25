Definition admit {T: Type} : T.  Admitted.

Inductive day : Type :=
  | monday : day
  | tuesday : day
  | wednesday : day
  | thursday : day
  | friday : day
  | saturday : day
  | sunday : day.

Definition next_weekday (d:day) : day :=
  match d with
  | monday    => tuesday
  | tuesday   => wednesday
  | wednesday => thursday
  | thursday  => friday
  | friday    => monday
  | saturday  => monday
  | sunday    => monday
  end.

Compute (next_weekday friday).

Compute (next_weekday (next_weekday saturday)).

Example test_next_weekday:
  (next_weekday (next_weekday saturday)) = tuesday.

Proof. simpl. reflexivity.  Qed.

Inductive bool : Type :=
  | true : bool
  | false : bool.

Definition negb (b:bool) : bool :=
  match b with
  | true => false
  | false => true
  end.

Definition andb (b1:bool) (b2:bool) : bool :=
  match b1 with
  | true => b2
  | false => false
  end.

Definition orb (b1:bool) (b2:bool) : bool :=
  match b1 with
  | true => true
  | false => b2
  end.

Example test_orb1:  (orb true  false) = true.
Proof. simpl. reflexivity.  Qed.
Example test_orb2:  (orb false false) = false.
Proof. simpl. reflexivity.  Qed.
Example test_orb3:  (orb false true)  = true.
Proof. simpl. reflexivity.  Qed.
Example test_orb4:  (orb true  true)  = true.
Proof. simpl. reflexivity.  Qed.


Infix "&&" := andb.
Infix "||" := orb.

Example test_orb5:  false || false || true = true.
Proof. simpl. reflexivity. Qed.

Check negb.
Definition nandb (b1:bool) (b2:bool) : bool :=
  negb (andb b1 b2).
Example test_nandb1:               (nandb true false) = true.
Proof. reflexivity. Qed.
Example test_nandb2:               (nandb false false) = true.
Proof. reflexivity. Qed.
Example test_nandb3:               (nandb false true) = true.
Proof. reflexivity. Qed.
Example test_nandb4:               (nandb true true) = false.
Proof. reflexivity. Qed.

Definition andb3 (b1:bool) (b2:bool) (b3:bool) : bool :=
  andb (andb b1 b2) b3.

Example test_andb31:                 (andb3 true true true) = true.
Proof. reflexivity. Qed.
Example test_andb32:                 (andb3 false true true) = false.
Proof. reflexivity. Qed.
Example test_andb33:                 (andb3 true false true) = false.
Proof. reflexivity. Qed.
Example test_andb34:                 (andb3 true true false) = false.
Proof. reflexivity. Qed.

Check true.
Check (negb true).

Check negb.

Module Playground1.

Inductive nat : Type :=
  | O : nat
  | S : nat -> nat.


Definition pred (n : nat) : nat :=
  match n with
    | O => O
    | S n' => n'
  end.

End Playground1.

Definition minustwo (n : nat) : nat :=
  match n with
    | O => O
    | S O => O
    | S (S n') => n'
  end.

Check (S (S (S (S O)))).
Compute (minustwo 4).

Check S.
Check pred.
Check minustwo.

Fixpoint evenb (n:nat) : bool :=
  match n with
  | O        => true
  | S O      => false
  | S (S n') => evenb n'
  end.

Definition oddb (n:nat) : bool   :=   negb (evenb n).

Example test_oddb1:    oddb 1 = true.
Proof. simpl. reflexivity.  Qed.
Example test_oddb2:    oddb 4 = false.
Proof. simpl. reflexivity.  Qed.

Module Playground2.

Fixpoint plus (n : nat) (m : nat) : nat :=
  match n with
    | O => m
    | S n' => S (plus n' m)
  end.

Compute (plus 3 2).


Fixpoint mult (n m : nat) : nat :=
  match n with
    | O => O
    | S n' => plus m (mult n' m)
  end.

Example test_mult1: (mult 3 3) = 9.
Proof. simpl. reflexivity.  Qed.


Fixpoint minus (n m:nat) : nat :=
  match n, m with
  | O   , _    => O
  | S _ , O    => n
  | S n', S m' => minus n' m'
  end.

End Playground2.

Fixpoint exp (base power : nat) : nat :=
  match power with
    | O => S O
    | S p => mult base (exp base p)
  end.

Fixpoint factorial (n:nat) : nat :=
  match n with
  | O => 1
  | S n' => n * (factorial n')
  end.

Example test_factorial1:          (factorial 3) = 6.
Proof. reflexivity. Qed.
Example test_factorial2:          (factorial 5) = (mult 10 12).
Proof. reflexivity. Qed.

Notation "x + y" := (plus x y)
                       (at level 50, left associativity)
                       : nat_scope.
Notation "x - y" := (minus x y)
                       (at level 50, left associativity)
                       : nat_scope.
Notation "x * y" := (mult x y)
                       (at level 40, left associativity)
                       : nat_scope.

Check ((0 + 1) + 1).

Fixpoint beq_nat (n m : nat) : bool :=
  match n with
  | O => match m with
         | O => true
         | S m' => false
         end
  | S n' => match m with
            | O => false
            | S m' => beq_nat n' m'
            end
  end.

Fixpoint leb (n m : nat) : bool :=
  match n with
  | O => true
  | S n' =>
      match m with
      | O => false
      | S m' => leb n' m'
      end
  end.

Example test_leb1:             (leb 2 2) = true.
Proof. simpl. reflexivity.  Qed.
Example test_leb2:             (leb 2 4) = true.
Proof. simpl. reflexivity.  Qed.
Example test_leb3:             (leb 4 2) = false.
Proof. simpl. reflexivity.  Qed.


Fixpoint blt_nat (n m : nat) : bool :=
  match m with
  | O => false
  | S m' =>
    match n with
    | O => true
    | S n' => blt_nat n' m'
    end
  end.

Example test_blt_nat1:             (blt_nat 2 2) = false.
Proof. reflexivity. Qed.
Example test_blt_nat2:             (blt_nat 2 4) = true.
Proof. reflexivity. Qed.
Example test_blt_nat3:             (blt_nat 4 2) = false.
Proof. reflexivity. Qed.

Theorem plus_O_n : forall n : nat, 0 + n = n.
Proof.
  intros n. simpl. reflexivity.  Qed.

Theorem plus_O_n' : forall n : nat, 0 + n = n.
Proof.
  intros n. reflexivity. Qed.

Theorem plus_1_l : forall n:nat, 1 + n = S n.
Proof.
  intros n. reflexivity.  Qed.

Theorem mult_0_l : forall n:nat, 0 * n = 0.
Proof.
  intros n. reflexivity.  Qed.

Theorem plus_n_O : forall n, n = n + 0.
Proof.
  intros n. simpl.


Abort.


Theorem plus_id_example : forall n m:nat,
  n = m ->
  n + n = m + m.

Proof.
  intros n m.
  intros H.
  rewrite -> H.
  reflexivity.  Qed.

Theorem plus_id_exercise : forall n m o : nat,
  n = m -> m = o -> n + m = m + o.
Proof.
  intros n m o H1 H2. rewrite -> H1. rewrite <- H2. reflexivity.
Qed.

Theorem mult_0_plus : forall n m : nat,
  (0 + n) * m = n * m.
Proof.
  intros n m.
  rewrite -> plus_O_n.
  reflexivity.  Qed.

Theorem mult_S_1 : forall n m : nat,
  m = S n ->
  m * (1 + n) = m * m.
Proof.
  intros n m H. simpl. rewrite <- H. reflexivity.
  Qed.


Theorem plus_1_neq_0_firsttry : forall n : nat,
  beq_nat (n + 1) 0 = false.
Proof.
  intros n.
  simpl.
Abort.

Theorem plus_1_neq_0 : forall n : nat,
  beq_nat (n + 1) 0 = false.
Proof.
  intros n. destruct n as [| n'].
  - reflexivity.
  - reflexivity.   Qed.

Theorem negb_involutive : forall b : bool,
  negb (negb b) = b.
Proof.
  intros b. destruct b.
  - reflexivity.
  - reflexivity.  Qed.


Theorem andb_commutative : forall b c, andb b c = andb c b.
Proof.
  intros b c. destruct b.
  - destruct c.
    + reflexivity.
    + reflexivity.
  - destruct c.
    + reflexivity.
    + reflexivity.
Qed.


Theorem andb_commutative' : forall b c, andb b c = andb c b.
Proof.
  intros b c. destruct b.
  { destruct c.
    { reflexivity. }
    { reflexivity. } }
  { destruct c.
    { reflexivity. }
    { reflexivity. } }
Qed.

Theorem andb3_exchange :
  forall b c d, andb (andb b c) d = andb (andb b d) c.
Proof.
  intros b c d. destruct b.
  - destruct c.
    { destruct d.
      - reflexivity.
      - reflexivity. }
    { destruct d.
      - reflexivity.
      - reflexivity. }
  - destruct c.
    { destruct d.
      - reflexivity.
      - reflexivity. }
    { destruct d.
      - reflexivity.
      - reflexivity. }
Qed.


Theorem plus_1_neq_0' : forall n : nat,
  beq_nat (n + 1) 0 = false.
Proof.
  intros [|n].
  - reflexivity.
  - reflexivity.  Qed.


Theorem andb_commutative'' :
  forall b c, andb b c = andb c b.
Proof.
  intros [] [].
  - reflexivity.
  - reflexivity.
  - reflexivity.
  - reflexivity.
Qed.


Theorem andb_true_elim2 : forall b c : bool,
  andb b c = true -> c = true.
Proof.
  intros [] [].
  - reflexivity.
  - simpl. intros H. rewrite -> H. reflexivity.
  - reflexivity.
  - simpl. intros H. rewrite -> H. reflexivity.
Qed.

Theorem zero_nbeq_plus_1 : forall n : nat,
  beq_nat 0 (n + 1) = false.
Proof.
  intros [|n].
  - reflexivity.
  - simpl. reflexivity.
Qed.


Notation "x + y" := (plus x y)
                       (at level 50, left associativity)
                       : nat_scope.
Notation "x * y" := (mult x y)
                       (at level 40, left associativity)
                       : nat_scope.


Fixpoint plus' (n : nat) (m : nat) : nat :=
  match n with
  | O => m
  | S n' => S (plus' n' m)
  end.


Theorem identity_fn_applied_twice :
  forall (f : bool -> bool),
  (forall (x : bool), f x = x) ->
  forall (b : bool), f (f b) = b.
Proof.
  intros f x b. rewrite -> x. rewrite -> x. reflexivity.
Qed.


Theorem negation_fn_applied_twice :
  forall (f : bool -> bool),
  (forall (x : bool), f x = negb x) ->
  forall (b : bool), f (f b) = b.
Proof.
  intros f x b. rewrite -> x. rewrite -> x. rewrite -> negb_involutive. reflexivity.
Qed.


Theorem andb_eq_orb :
  forall (b c : bool),
  (andb b c = orb b c) ->
  b = c.
Proof.
  intros [] [].
  - reflexivity.
  - simpl. intros H. rewrite -> H. reflexivity.
  - simpl. intros H. rewrite -> H. reflexivity.
  - reflexivity.
Qed.

Print nat.


Inductive bin : Type :=
 | EOB : bin
 | N : bin -> bin
 | E : bin -> bin.

Fixpoint incr (n : bin) : bin :=
  match n with
  | EOB => E EOB
  | N n' => E n'
  | E n' => N (incr n')
  end.

Fixpoint bin_to_nat (b : bin) : nat :=
  match b with
  | EOB => 0
  | N b' => 2 * (bin_to_nat b')
  | E b' => 1 + 2 * (bin_to_nat b')
  end.

Example test_bin_incr1 :=
  bin_to_nat(incr (E (E (E (N EOB))))).


Theorem plus_n_O_firsttry : forall n:nat,
  n = n + 0.

Proof.
  intros n.
  simpl.
Abort.

Theorem plus_n_O_secondtry : forall n:nat,
  n = n + 0.
Proof.
  intros n. destruct n as [| n'].
  - (* n = 0 *)
    reflexivity.
  - (* n = S n' *)
    simpl.
Abort.

Theorem plus_n_O : forall n:nat, n = n + 0.
Proof.
  intros n. induction n as [| n' IHn'].
  - (* n = 0 *)    reflexivity.
  - (* n = S n' *) simpl. rewrite <- IHn'. reflexivity.  Qed.

Theorem minus_diag : forall n,
  minus n n = 0.
Proof.
  (* WORKED IN CLASS *)
  intros n. induction n as [| n' IHn'].
  - (* n = 0 *)
    simpl. reflexivity.
  - (* n = S n' *)
    simpl. rewrite -> IHn'. reflexivity.  Qed.


Theorem mult_0_r : forall n:nat,
  n * 0 = 0.
Proof.
  intros n. induction n.
  - reflexivity.
  - simpl. rewrite -> IHn. reflexivity.
Qed.

Theorem plus_n_Sm : forall n m : nat, 
  S (n + m) = n + (S m).
Proof.
  intros n m. induction n as [| n' IHn'].
  - reflexivity.
  - simpl. rewrite -> IHn'. reflexivity.
Qed.

Theorem plus_comm : forall n m : nat,
  n + m = m + n.
Proof.
  intros n m. induction n as [| n' IHn'].
  - simpl. rewrite <- plus_n_O. reflexivity.
  - rewrite <- plus_n_Sm. rewrite <- IHn'. reflexivity.
Qed.

Theorem plus_assoc : forall n m p : nat,
  n + (m + p) = (n + m) + p.
Proof.
  intros n m p. induction n as [|n' IHn'].
  - reflexivity.
  - simpl. rewrite <- IHn'. reflexivity.
Qed.


Fixpoint double (n:nat) :=
  match n with
  | O => O
  | S n' => S (S (double n'))
  end.


Lemma double_plus : forall n, double n = n + n .
Proof.
  intros n. induction n as [|n' IHn'].
  - reflexivity.
  - simpl. rewrite -> IHn'. rewrite -> plus_n_Sm. reflexivity.
Qed.

Theorem evenb_S : forall n : nat,
  evenb (S n) = negb (evenb n).
Proof.
  intros. induction n as [|n' IHn'].
  - reflexivity.
  - rewrite -> IHn'. rewrite -> negb_involutive. reflexivity.
Qed.


Theorem mult_0_plus' : forall n m : nat,
  (0 + n) * m = n * m.
Proof.
  intros n m.
  assert (H: 0 + n = n). { reflexivity. }
  rewrite -> H.
  reflexivity.  Qed.


Theorem plus_rearrange_firsttry : forall n m p q : nat,
  (n + m) + (p + q) = (m + n) + (p + q).
Proof.
  intros n m p q.
  rewrite -> plus_comm.
Abort.

Theorem plus_rearrange : forall n m p q : nat,
  (n + m) + (p + q) = (m + n) + (p + q).
Proof.
  intros n m p q.
  assert (H: n + m = m + n).
  { rewrite -> plus_comm. reflexivity. }
  rewrite -> H. reflexivity.  Qed.

Theorem plus_swap : forall n m p : nat,
  n + (m + p) = m + (n + p).
Proof.
  intros n m p.
  rewrite -> plus_assoc.
  assert (H: n + m = m + n). { rewrite -> plus_comm. reflexivity. } rewrite -> H.
  rewrite -> plus_assoc. reflexivity.
Qed.


Lemma mult_n_Sm : forall m n : nat,
    n * (S m) = n + n * m.
Proof.
  intros n m. induction m.
  - reflexivity.
  - simpl. rewrite -> IHm. rewrite -> plus_swap. reflexivity.
Qed.

Theorem mult_comm : forall m n : nat,
  m * n = n * m.
Proof.
  intros m n. induction m.
  - rewrite -> mult_0_r. reflexivity.
  - rewrite -> mult_n_Sm. simpl. rewrite -> IHm. reflexivity.
Qed.

Theorem leb_refl : forall n:nat,
  true = leb n n.
Proof.
  intros n. induction n as [|n' IHn'].
  - reflexivity.
  - simpl. rewrite <- IHn'. reflexivity.
Qed.

Theorem zero_nbeq_S : forall n:nat,
  beq_nat 0 (S n) = false.
Proof.
  Print beq_nat. reflexivity.
Qed.

Theorem andb_false_r : forall b : bool,
  andb b false = false.
Proof.
  intros b. destruct b.
  - reflexivity.
  - reflexivity.
Qed.

Theorem plus_ble_compat_l : forall n m p : nat,
  leb n m = true -> leb (p + n) (p + m) = true.
Proof.
  intros n m p H. induction p as [|p' IHp'].
  - simpl. rewrite -> H. reflexivity.
  - simpl. rewrite -> IHp'. reflexivity.
Qed.

Theorem S_nbeq_0 : forall n:nat,
  beq_nat (S n) 0 = false.
Proof.
Print beq_nat.
  reflexivity.
Qed.

Theorem mult_1_l : forall n:nat, 1 * n = n.
Proof.
  intros n.
  simpl. rewrite <- plus_n_O. reflexivity.
Qed.

Theorem all3_spec : forall b c : bool,
    orb
      (andb b c)
      (orb (negb b)
               (negb c))
  = true.
Proof.
  intros [] [].
  - reflexivity.
  - reflexivity.
  - reflexivity.
  - reflexivity.
Qed.

Theorem mult_plus_distr_r : forall n m p : nat,
  (n + m) * p = (n * p) + (m * p).
Proof.
  intros n m p. induction n.
  - simpl. reflexivity.
  - simpl. rewrite -> IHn. rewrite -> plus_assoc. reflexivity.
Qed.

Theorem mult_assoc : forall n m p : nat,
  n * (m * p) = (n * m) * p.
Proof.
  intros n m p. induction n.
  - simpl. reflexivity.
  - simpl. rewrite -> IHn. rewrite -> mult_plus_distr_r. reflexivity.
Qed.


Theorem beq_nat_refl : forall n : nat,
  true = beq_nat n n.
Proof.
  intros n. induction n.
  - reflexivity.
  - simpl. rewrite <- IHn. reflexivity.
Qed.


Theorem plus_swap' : forall n m p : nat,
  n + (m + p) = m + (n + p).
Proof.
  intros n m p. rewrite -> plus_assoc. rewrite -> plus_assoc.
  replace (n + m) with (m + n). reflexivity.
  rewrite -> plus_comm. reflexivity.
Qed.  


Theorem bin_to_nat_pres_incr : forall b : bin,
      bin_to_nat (incr b) = S (bin_to_nat b).
Proof.
 intros b. induction b.
 - reflexivity.
 - simpl. rewrite <- plus_n_O. reflexivity.
 - simpl. rewrite -> IHb. rewrite <- plus_n_O. rewrite <- plus_n_O.
   rewrite -> plus_n_Sm. simpl. reflexivity. Qed.

Theorem plus_assoc' : forall n m p : nat,
  n + (m + p) = (n + m) + p.
Proof. intros n m p. induction n as [| n' IHn']. reflexivity.
  simpl. rewrite -> IHn'. reflexivity.  Qed.


Theorem plus_assoc'' : forall n m p : nat,
  n + (m + p) = (n + m) + p.
Proof.
  intros n m p. induction n as [| n' IHn'].
  - (* n = 0 *)
    reflexivity.
  - (* n = S n' *)
    simpl. rewrite -> IHn'. reflexivity.   Qed.

Inductive natprod : Type :=
| pair : nat -> nat -> natprod.


Check (pair 3 5).


Definition fst (p : natprod) : nat :=
  match p with
  | pair x y => x
  end.

Definition snd (p : natprod) : nat :=
  match p with
  | pair x y => y
  end.

Compute (fst (pair 3 5)).

Notation "( x , y )" := (pair x y).


Compute (fst (3,5)).

Definition fst' (p : natprod) : nat :=
  match p with
  | (x,y) => x
  end.

Definition snd' (p : natprod) : nat :=
  match p with
  | (x,y) => y
  end.

Definition swap_pair (p : natprod) : natprod :=
  match p with
  | (x,y) => (y,x)
  end.


Theorem surjective_pairing' : forall (n m : nat),
  (n,m) = (fst (n,m), snd (n,m)).
Proof.
  reflexivity. Qed.


Theorem surjective_pairing_stuck : forall (p : natprod),
  p = (fst p, snd p).
Proof.
  simpl. (* Doesn't reduce anything! *)
Abort.

Theorem surjective_pairing : forall (p : natprod),
  p = (fst p, snd p).
Proof.
  intros p.  destruct p as [n m].  simpl.  reflexivity.  Qed.

Theorem snd_fst_is_swap : forall (p : natprod),
  (snd p, fst p) = swap_pair p.
Proof.
  intros p. destruct p as [n m].  simpl. reflexivity.
Qed.

Theorem fst_swap_is_snd : forall (p : natprod),
  fst (swap_pair p) = snd p.
Proof.
  intros p. destruct p as [n m]. reflexivity.  
Qed.

Inductive natlist : Type :=
  | nil  : natlist
  | cons : nat -> natlist -> natlist.

(** For example, here is a three-element list: *)

Definition mylist := cons 1 (cons 2 (cons 3 nil)).


Notation "x :: l" := (cons x l)
                     (at level 60, right associativity).
Notation "[ ]" := nil.
Notation "[ x ; .. ; y ]" := (cons x .. (cons y nil) ..).

Definition mylist1 := 1 :: (2 :: (3 :: nil)).
Definition mylist2 := 1 :: 2 :: 3 :: nil.
Definition mylist3 := [1;2;3].


Fixpoint repeat (n count : nat) : natlist :=
  match count with
  | O => nil
  | S count' => n :: (repeat n count')
  end.

Fixpoint length (l:natlist) : nat :=
  match l with
  | nil => O
  | h :: t => S (length t)
  end.

Fixpoint app (l1 l2 : natlist) : natlist :=
  match l1 with
  | nil    => l2
  | h :: t => h :: (app t l2)
  end.

Notation "x ++ y" := (app x y)
                     (right associativity, at level 60).

Example test_app1:             [1;2;3] ++ [4;5] = [1;2;3;4;5].
Proof. reflexivity.  Qed.
Example test_app2:             nil ++ [4;5] = [4;5].
Proof. reflexivity.  Qed.
Example test_app3:             [1;2;3] ++ nil = [1;2;3].
Proof. reflexivity.  Qed.

Definition hd (default:nat) (l:natlist) : nat :=
  match l with
  | nil => default
  | h :: t => h
  end.

Definition tl (l:natlist) : natlist :=
  match l with
  | nil => nil
  | h :: t => t
  end.

Example test_hd1:             hd 0 [1;2;3] = 1.
Proof. reflexivity.  Qed.
Example test_hd2:             hd 0 [] = 0.
Proof. reflexivity.  Qed.
Example test_tl:              tl [1;2;3] = [2;3].
Proof. reflexivity.  Qed.

Fixpoint nonzeros (l:natlist) : natlist :=
  match l with
  | nil => nil
  | h :: t => if(beq_nat h 0) then nonzeros t else h :: nonzeros t end.

Example test_nonzeros:
  nonzeros [0;1;0;2;3;0;0] = [1;2;3].
Proof.  reflexivity. Qed.

Fixpoint oddmembers (l:natlist) : natlist :=
  match l with
  | nil => nil
  | h :: t => if(oddb h) then h :: oddmembers t else oddmembers t end.

Example test_oddmembers:
  oddmembers [0;1;0;2;3;0;0] = [1;3].
Proof. reflexivity. Qed.

Fixpoint countoddmembers (l:natlist) : nat :=
  match l with
  | nil => 0
  | h :: t => if(oddb h) then 1 + (countoddmembers t) else countoddmembers t end.

Example test_countoddmembers1:
  countoddmembers [1;0;3;1;4;5] = 4.
Proof. reflexivity. Qed.

Example test_countoddmembers2:
  countoddmembers [0;2;4] = 0.
Proof. reflexivity. Qed.

Example test_countoddmembers3:
  countoddmembers nil = 0.
Proof. reflexivity. Qed. (** [] *)


Fixpoint alternate (l1 l2 : natlist) : natlist :=
  match l1, l2 with
  | nil, nil => nil
  | nil, _ => l2
  | _, nil => l1
  | h1 :: t1, h2 :: t2 => h1 :: h2 :: alternate t1 t2 end.

Example test_alternate1:
  alternate [1;2;3] [4;5;6] = [1;4;2;5;3;6].
Proof. reflexivity. Qed.

Example test_alternate2:
  alternate [1] [4;5;6] = [1;4;5;6].
Proof. reflexivity. Qed.

Example test_alternate3:
  alternate [1;2;3] [4] = [1;4;2;3].
Proof. reflexivity. Qed.

Example test_alternate4:
  alternate [] [20;30] = [20;30].
Proof. reflexivity. Qed.


Definition bag := natlist.


Fixpoint count (v:nat) (s:bag) : nat :=
  match s with
  | nil => 0
  | h :: t => if(beq_nat v h) then 1 + (count v t) else count v t end.


Example test_count1:              count 1 [1;2;3;1;4;1] = 3.
Proof. reflexivity. Qed.

Example test_count2:              count 6 [1;2;3;1;4;1] = 0.
Proof. reflexivity. Qed.


Definition sum : bag -> bag -> bag :=
  fun l1 l2 => app l1 l2.

Example test_sum1:              count 1 (sum [1;2;3] [1;4;1]) = 3.
Proof. simpl. reflexivity. Qed.

Definition add (v:nat) (s:bag) : bag := app [v] s.

Example test_add1:                count 1 (add 1 [1;4;1]) = 3.
Proof. simpl. reflexivity. Qed.

Example test_add2:                count 5 (add 1 [1;4;1]) = 0.
Proof. simpl. reflexivity. Qed.

Fixpoint member (v:nat) (s:bag) : bool :=
  match s with
  | nil => false
  | h :: t => if(beq_nat v h) then true else member v t end.

Example test_member1:             member 1 [1;4;1] = true.
Proof. simpl. reflexivity. Qed.

Example test_member2:             member 2 [1;4;1] = false.
Proof. simpl. reflexivity. Qed.


Fixpoint remove_one (v:nat) (s:bag) : bag :=
  match s with
  | nil => nil
  | h :: t => if(beq_nat v h) then t else h :: (remove_one v t) end.

Example test_remove_one1:
  count 5 (remove_one 5 [2;1;5;4;1]) = 0.
Proof. reflexivity. Qed.

Example test_remove_one2:
  count 5 (remove_one 5 [2;1;4;1]) = 0.
Proof. reflexivity. Qed.

Example test_remove_one3:
  count 4 (remove_one 5 [2;1;4;5;1;4]) = 2.
Proof. reflexivity. Qed.

Example test_remove_one4:
  count 5 (remove_one 5 [2;1;5;4;5;1;4]) = 1.
Proof. reflexivity. Qed.

Fixpoint remove_all (v:nat) (s:bag) : bag :=
  match s with
  | nil => nil
  | h :: t => if(beq_nat v h) then remove_all v t else h :: remove_all v t end.

Example test_remove_all1:  count 5 (remove_all 5 [2;1;5;4;1]) = 0.
Proof. reflexivity. Qed.

Example test_remove_all2:  count 5 (remove_all 5 [2;1;4;1]) = 0.
Proof. reflexivity. Qed.

Example test_remove_all3:  count 4 (remove_all 5 [2;1;4;5;1;4]) = 2.
Proof. reflexivity. Qed.

Example test_remove_all4:  count 5 (remove_all 5 [2;1;5;4;5;1;4;5;1;4]) = 0.
Proof. reflexivity. Qed.

Fixpoint exist (v:nat) (s:bag) : bool :=
  match s with
  | nil => false
  | h :: t => if(beq_nat v h) then true else exist v t end.


Fixpoint subset (s1:bag) (s2:bag) : bool :=
  match s1 with
  | nil => true
  | h :: t => if(exist h s2) then subset t (remove_one h s2) else false end.

Example test_subset1:              subset [1;2] [2;1;4;1] = true.
Proof. reflexivity. Qed.

Example test_subset2:              subset [1;2;2] [2;1;4;1] = false.
Proof. reflexivity. Qed.

Theorem nil_app : forall l:natlist,
  [] ++ l = l.
Proof. reflexivity. Qed.

Theorem tl_length_pred : forall l:natlist,
  pred (length l) = length (tl l).
Proof.
  intros l. destruct l as [| n l'].
  - (* l = nil *)
    reflexivity.
  - (* l = cons n l' *)
    reflexivity.  Qed.

Theorem app_assoc : forall l1 l2 l3 : natlist,
  (l1 ++ l2) ++ l3 = l1 ++ (l2 ++ l3).
Proof.
  intros l1 l2 l3. induction l1 as [| n l1' IHl1'].
  - (* l1 = nil *)
    reflexivity.
  - (* l1 = cons n l1' *)
    simpl. rewrite -> IHl1'. reflexivity.  Qed.

Fixpoint rev (l:natlist) : natlist :=
  match l with
  | nil    => nil
  | h :: t => rev t ++ [h]
  end.

Example test_rev1:            rev [1;2;3] = [3;2;1].
Proof. reflexivity.  Qed.
Example test_rev2:            rev nil = nil.
Proof. reflexivity.  Qed.

Theorem rev_length_firsttry : forall l : natlist,
  length (rev l) = length l.
Proof.
  intros l. induction l as [| n l' IHl'].
  - (* l = [] *)
    reflexivity.
  - (* l = n :: l' *)
    simpl.
    rewrite <- IHl'.
Abort.


Theorem app_length : forall l1 l2 : natlist,
  length (l1 ++ l2) = (length l1) + (length l2).
Proof.
  (* WORKED IN CLASS *)
  intros l1 l2. induction l1 as [| n l1' IHl1'].
  - (* l1 = nil *)
    reflexivity.
  - (* l1 = cons *)
    simpl. rewrite -> IHl1'. reflexivity.  Qed.

Theorem rev_length : forall l : natlist,
  length (rev l) = length l.
Proof.
  intros l. induction l as [| n l' IHl'].
  - (* l = nil *)
    reflexivity.
  - (* l = cons *)
    simpl. rewrite -> app_length, plus_comm.
    rewrite -> IHl'. reflexivity.  Qed.



Theorem app_nil_r : forall l : natlist,
  l ++ [] = l.
Proof.
  intros l. induction l.
  - simpl. reflexivity.
  - simpl. rewrite -> IHl. reflexivity.
Qed.

Theorem rev_assoc : forall l1 l2 : natlist,
    rev(l1 ++ l2) = (rev l2) ++ (rev l1).
Proof.
  intros l1 l2. induction l1.
  - simpl. rewrite -> app_nil_r. reflexivity.
  - simpl. rewrite -> IHl1. rewrite -> app_assoc. reflexivity.
Qed.

Theorem rev_involutive : forall l : natlist,
  rev (rev l) = l.
Proof.
  intros l. induction l.
  - simpl. reflexivity.
  - simpl. rewrite -> rev_assoc. rewrite -> IHl. reflexivity.
Qed.


Theorem app_assoc4 : forall l1 l2 l3 l4 : natlist,
  l1 ++ (l2 ++ (l3 ++ l4)) = ((l1 ++ l2) ++ l3) ++ l4.
Proof.
  intros l1 l2 l3 l4. rewrite -> app_assoc. rewrite -> app_assoc. reflexivity.
Qed.

Lemma nonzeros_app : forall l1 l2 : natlist,
  nonzeros (l1 ++ l2) = (nonzeros l1) ++ (nonzeros l2).
Proof.
  intros l1 l2. induction l1.
  - simpl. reflexivity.
  - simpl. { induction n.
             - simpl. rewrite -> IHl1. reflexivity.
             - simpl. rewrite -> IHl1. reflexivity. }
Qed.


Fixpoint beq_natlist (l1 l2 : natlist) : bool :=
  match l1, l2 with
  | nil, nil => true
  | _, nil => false
  | nil, _ => false
  | h1 :: t1, h2 :: t2 => if(beq_nat h1 h2) then beq_natlist t1 t2 else false end.

Example test_beq_natlist1 :
  (beq_natlist nil nil = true).
Proof. reflexivity. Qed.

Example test_beq_natlist2 :
  beq_natlist [1;2;3] [1;2;3] = true.
Proof. reflexivity. Qed.

Example test_beq_natlist3 :
  beq_natlist [1;2;3] [1;2;4] = false.
Proof. reflexivity. Qed.

Theorem beq_natlist_refl : forall l:natlist,
  true = beq_natlist l l.
Proof.
  intros l. induction l.
  - reflexivity.
  - simpl. rewrite <- IHl. rewrite <- beq_nat_refl. reflexivity.
Qed.


Print leb.


Theorem count_member_nonzero : forall (s : bag),
  leb 1 (count 1 (1 :: s)) = true.
Proof.
  intros s. induction s.
  - simpl. reflexivity.
  - simpl. reflexivity.
Qed.


Theorem ble_n_Sn : forall n,
  leb n (S n) = true.
Proof.
  intros n. induction n as [| n' IHn'].
  - (* 0 *)
    simpl.  reflexivity.
  - (* S n' *)
    simpl.  rewrite IHn'.  reflexivity.  Qed.

Theorem remove_decreases_count: forall (s : bag),
  leb (count 0 (remove_one 0 s)) (count 0 s) = true.
Proof.
  intros s. induction s.
  - simpl. reflexivity.
  - simpl. { induction n.
             - simpl. rewrite ble_n_Sn. reflexivity.
             - simpl. rewrite IHs. reflexivity. }
Qed.


Theorem bag_count_sum : forall s1 s2 : bag, forall v : nat,
      count v (sum s1 s2) = (count v s1) + (count v s2).
Proof.
  intros s1 s2 v. induction s1 as [|n1 s1' IHs1].
  - simpl. reflexivity.
  - simpl. rewrite -> IHs1. { induction s2 as [|n2 s2' IHs2].
                              - simpl. rewrite <- plus_n_O. rewrite <- plus_n_O. reflexivity.
                                - simpl.
Abort.

Theorem rev_injective : forall l1 l2 : natlist,
    rev l1 = rev l2 -> l1 = l2.
Proof.
  intros l1 l2 H. rewrite <- rev_involutive. rewrite <- H. rewrite -> rev_involutive. reflexivity.
Qed.


Fixpoint nth_bad (l:natlist) (n:nat) : nat :=
  match l with
  | nil => 42  (* arbitrary! *)
  | a :: l' => match beq_nat n O with
               | true => a
               | false => nth_bad l' (pred n)
               end
  end.

Inductive natoption : Type :=
  | Some : nat -> natoption
  | None : natoption.

Fixpoint nth_error (l:natlist) (n:nat) : natoption :=
  match l with
  | nil => None
  | a :: l' => match beq_nat n O with
               | true => Some a
               | false => nth_error l' (pred n)
               end
  end.

Example test_nth_error1 : nth_error [4;5;6;7] 0 = Some 4.
Proof. reflexivity. Qed.
Example test_nth_error2 : nth_error [4;5;6;7] 3 = Some 7.
Proof. reflexivity. Qed.
Example test_nth_error3 : nth_error [4;5;6;7] 9 = None.
Proof. reflexivity. Qed.

(** (In the HTML version, the boilerplate proofs of these
    examples are elided.  Click on a box if you want to see one.)
    This example is also an opportunity to introduce one more small
    feature of Coq's programming language: conditional
    expressions... *)

Fixpoint nth_error' (l:natlist) (n:nat) : natoption :=
  match l with
  | nil => None
  | a :: l' => if beq_nat n O then Some a
               else nth_error' l' (pred n)
  end.

Definition option_elim (d : nat) (o : natoption) : nat :=
  match o with
  | Some n' => n'
  | None => d
  end.

Definition hd_error (l : natlist) : natoption :=
  match l with
  | nil => None
  | a :: l => Some a
  end.

Example test_hd_error1 : hd_error [] = None.
Proof. reflexivity. Qed.

Example test_hd_error2 : hd_error [1] = Some 1.
Proof. reflexivity. Qed.

Example test_hd_error3 : hd_error [5;6] = Some 5.
Proof. reflexivity. Qed.

Theorem option_elim_hd : forall (l:natlist) (default:nat),
  hd default l = option_elim default (hd_error l).
Proof.
  intros l d. induction l as [|l' IHl'].
  - simpl. reflexivity.
  - simpl. reflexivity.
Qed.



Inductive id : Type :=
  | Id : nat -> id.

Definition beq_id x1 x2 :=
  match x1, x2 with
  | Id n1, Id n2 => beq_nat n1 n2
  end.

(** **** Exercise: 1 star (beq_id_refl)  *)
Theorem beq_id_refl : forall x, true = beq_id x x.
Proof.
  intros x. destruct x as [n]. simpl. rewrite <- beq_nat_refl. reflexivity.
Qed.

(** Now we define the type of partial maps: *)


Inductive partial_map : Type :=
  | empty  : partial_map
  | record : id -> nat -> partial_map -> partial_map.

Definition update (d : partial_map)
                  (key : id) (value : nat)
                  : partial_map :=
  record key value d.

Fixpoint find (key : id) (d : partial_map) : natoption :=
  match d with
  | empty         => None
  | record k v d' => if beq_id key k
                     then Some v
                     else find key d'
  end.

(** **** Exercise: 1 star (update_eq)  *)
Theorem update_eq :
  forall (d : partial_map) (k : id) (v: nat),
    find k (update d k v) = Some v.
Proof.
  intros d k v. simpl. rewrite <- beq_id_refl. reflexivity.
Qed.

(** **** Exercise: 1 star (update_neq)  *)
Theorem update_neq :
  forall (d : partial_map) (m n : id) (o: nat),
    beq_id m n = false -> find m (update d n o) = find m d.
Proof.
  intros d m n o H. simpl. rewrite -> H. reflexivity.
Qed.


Inductive baz : Type :=
  | Baz1 : baz -> baz
  | Baz2 : baz -> bool -> baz.
