// NOTE: Assertions have been autogenerated by utils/update_cc_test_checks.py
// RUN: %clang_cc1 -O1 -disable-llvm-passes -emit-llvm %s -o - -triple=x86_64-linux-gnu -verify
// RUN: %clang_cc1 -O1 -disable-llvm-passes -emit-llvm %s -o - -triple=x86_64-linux-gnu | FileCheck %s

// CHECK-LABEL: @_Z2wli(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[E_ADDR:%.*]] = alloca i32, align 4
// CHECK-NEXT:    store i32 [[E:%.*]], ptr [[E_ADDR]], align 4, !tbaa [[TBAA2:![0-9]+]]
// CHECK-NEXT:    br label [[WHILE_COND:%.*]]
// CHECK:       while.cond:
// CHECK-NEXT:    [[TMP0:%.*]] = load i32, ptr [[E_ADDR]], align 4, !tbaa [[TBAA2]]
// CHECK-NEXT:    [[TOBOOL:%.*]] = icmp ne i32 [[TMP0]], 0
// CHECK-NEXT:    [[TOBOOL_EXPVAL:%.*]] = call i1 @llvm.expect.i1(i1 [[TOBOOL]], i1 true)
// CHECK-NEXT:    br i1 [[TOBOOL_EXPVAL]], label [[WHILE_BODY:%.*]], label [[WHILE_END:%.*]]
// CHECK:       while.body:
// CHECK-NEXT:    [[TMP1:%.*]] = load i32, ptr [[E_ADDR]], align 4, !tbaa [[TBAA2]]
// CHECK-NEXT:    [[INC:%.*]] = add nsw i32 [[TMP1]], 1
// CHECK-NEXT:    store i32 [[INC]], ptr [[E_ADDR]], align 4, !tbaa [[TBAA2]]
// CHECK-NEXT:    br label [[WHILE_COND]], !llvm.loop [[LOOP6:![0-9]+]]
// CHECK:       while.end:
// CHECK-NEXT:    ret void
//
void wl(int e){
  while(e) [[likely]] ++e;
}

// CHECK-LABEL: @_Z2wui(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[E_ADDR:%.*]] = alloca i32, align 4
// CHECK-NEXT:    store i32 [[E:%.*]], ptr [[E_ADDR]], align 4, !tbaa [[TBAA2]]
// CHECK-NEXT:    br label [[WHILE_COND:%.*]]
// CHECK:       while.cond:
// CHECK-NEXT:    [[TMP0:%.*]] = load i32, ptr [[E_ADDR]], align 4, !tbaa [[TBAA2]]
// CHECK-NEXT:    [[TOBOOL:%.*]] = icmp ne i32 [[TMP0]], 0
// CHECK-NEXT:    [[TOBOOL_EXPVAL:%.*]] = call i1 @llvm.expect.i1(i1 [[TOBOOL]], i1 false)
// CHECK-NEXT:    br i1 [[TOBOOL_EXPVAL]], label [[WHILE_BODY:%.*]], label [[WHILE_END:%.*]]
// CHECK:       while.body:
// CHECK-NEXT:    [[TMP1:%.*]] = load i32, ptr [[E_ADDR]], align 4, !tbaa [[TBAA2]]
// CHECK-NEXT:    [[INC:%.*]] = add nsw i32 [[TMP1]], 1
// CHECK-NEXT:    store i32 [[INC]], ptr [[E_ADDR]], align 4, !tbaa [[TBAA2]]
// CHECK-NEXT:    br label [[WHILE_COND]], !llvm.loop [[LOOP9:![0-9]+]]
// CHECK:       while.end:
// CHECK-NEXT:    ret void
//
void wu(int e){
  while(e) [[unlikely]] ++e;
}

// CHECK-LABEL: @_Z15w_branch_elidedj(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[E_ADDR:%.*]] = alloca i32, align 4
// CHECK-NEXT:    store i32 [[E:%.*]], ptr [[E_ADDR]], align 4, !tbaa [[TBAA2]]
// CHECK-NEXT:    br label [[WHILE_BODY:%.*]]
// CHECK:       while.body:
// CHECK-NEXT:    [[TMP0:%.*]] = load i32, ptr [[E_ADDR]], align 4, !tbaa [[TBAA2]]
// CHECK-NEXT:    [[INC:%.*]] = add i32 [[TMP0]], 1
// CHECK-NEXT:    store i32 [[INC]], ptr [[E_ADDR]], align 4, !tbaa [[TBAA2]]
// CHECK-NEXT:    br label [[WHILE_BODY]], !llvm.loop [[LOOP10:![0-9]+]]
//
void w_branch_elided(unsigned e){
  // expected-warning@+2 {{attribute 'likely' has no effect when annotating an infinite loop}}
  // expected-note@+1 {{annotating the infinite loop here}}
  while(1) [[likely]] ++e;
}

// CHECK-LABEL: @_Z2flj(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[E_ADDR:%.*]] = alloca i32, align 4
// CHECK-NEXT:    [[I:%.*]] = alloca i32, align 4
// CHECK-NEXT:    store i32 [[E:%.*]], ptr [[E_ADDR]], align 4, !tbaa [[TBAA2]]
// CHECK-NEXT:    call void @llvm.lifetime.start.p0(i64 4, ptr [[I]]) #[[ATTR3:[0-9]+]]
// CHECK-NEXT:    store i32 0, ptr [[I]], align 4, !tbaa [[TBAA2]]
// CHECK-NEXT:    br label [[FOR_COND:%.*]]
// CHECK:       for.cond:
// CHECK-NEXT:    [[TMP0:%.*]] = load i32, ptr [[I]], align 4, !tbaa [[TBAA2]]
// CHECK-NEXT:    [[TMP1:%.*]] = load i32, ptr [[E_ADDR]], align 4, !tbaa [[TBAA2]]
// CHECK-NEXT:    [[CMP:%.*]] = icmp ne i32 [[TMP0]], [[TMP1]]
// CHECK-NEXT:    [[CMP_EXPVAL:%.*]] = call i1 @llvm.expect.i1(i1 [[CMP]], i1 true)
// CHECK-NEXT:    br i1 [[CMP_EXPVAL]], label [[FOR_BODY:%.*]], label [[FOR_COND_CLEANUP:%.*]]
// CHECK:       for.cond.cleanup:
// CHECK-NEXT:    call void @llvm.lifetime.end.p0(i64 4, ptr [[I]]) #[[ATTR3]]
// CHECK-NEXT:    br label [[FOR_END:%.*]]
// CHECK:       for.body:
// CHECK-NEXT:    br label [[FOR_INC:%.*]]
// CHECK:       for.inc:
// CHECK-NEXT:    [[TMP2:%.*]] = load i32, ptr [[E_ADDR]], align 4, !tbaa [[TBAA2]]
// CHECK-NEXT:    [[INC:%.*]] = add i32 [[TMP2]], 1
// CHECK-NEXT:    store i32 [[INC]], ptr [[E_ADDR]], align 4, !tbaa [[TBAA2]]
// CHECK-NEXT:    br label [[FOR_COND]], !llvm.loop [[LOOP11:![0-9]+]]
// CHECK:       for.end:
// CHECK-NEXT:    ret void
//
void fl(unsigned e)
{
  for(int i = 0; i != e; ++e) [[likely]];
}

// CHECK-LABEL: @_Z2fui(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[E_ADDR:%.*]] = alloca i32, align 4
// CHECK-NEXT:    [[I:%.*]] = alloca i32, align 4
// CHECK-NEXT:    store i32 [[E:%.*]], ptr [[E_ADDR]], align 4, !tbaa [[TBAA2]]
// CHECK-NEXT:    call void @llvm.lifetime.start.p0(i64 4, ptr [[I]]) #[[ATTR3]]
// CHECK-NEXT:    store i32 0, ptr [[I]], align 4, !tbaa [[TBAA2]]
// CHECK-NEXT:    br label [[FOR_COND:%.*]]
// CHECK:       for.cond:
// CHECK-NEXT:    [[TMP0:%.*]] = load i32, ptr [[I]], align 4, !tbaa [[TBAA2]]
// CHECK-NEXT:    [[TMP1:%.*]] = load i32, ptr [[E_ADDR]], align 4, !tbaa [[TBAA2]]
// CHECK-NEXT:    [[CMP:%.*]] = icmp ne i32 [[TMP0]], [[TMP1]]
// CHECK-NEXT:    [[CMP_EXPVAL:%.*]] = call i1 @llvm.expect.i1(i1 [[CMP]], i1 false)
// CHECK-NEXT:    br i1 [[CMP_EXPVAL]], label [[FOR_BODY:%.*]], label [[FOR_COND_CLEANUP:%.*]]
// CHECK:       for.cond.cleanup:
// CHECK-NEXT:    call void @llvm.lifetime.end.p0(i64 4, ptr [[I]]) #[[ATTR3]]
// CHECK-NEXT:    br label [[FOR_END:%.*]]
// CHECK:       for.body:
// CHECK-NEXT:    br label [[FOR_INC:%.*]]
// CHECK:       for.inc:
// CHECK-NEXT:    [[TMP2:%.*]] = load i32, ptr [[E_ADDR]], align 4, !tbaa [[TBAA2]]
// CHECK-NEXT:    [[INC:%.*]] = add nsw i32 [[TMP2]], 1
// CHECK-NEXT:    store i32 [[INC]], ptr [[E_ADDR]], align 4, !tbaa [[TBAA2]]
// CHECK-NEXT:    br label [[FOR_COND]], !llvm.loop [[LOOP12:![0-9]+]]
// CHECK:       for.end:
// CHECK-NEXT:    ret void
//
void fu(int e)
{
  for(int i = 0; i != e; ++e) [[unlikely]];
}

// CHECK-LABEL: @_Z15f_branch_elidedv(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    br label [[FOR_COND:%.*]]
// CHECK:       for.cond:
// CHECK-NEXT:    br label [[FOR_COND]], !llvm.loop [[LOOP13:![0-9]+]]
//
void f_branch_elided()
{
  for(;;) [[likely]];
}

// CHECK-LABEL: @_Z3frlOA4_i(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[E_ADDR:%.*]] = alloca ptr, align 8
// CHECK-NEXT:    [[__RANGE1:%.*]] = alloca ptr, align 8
// CHECK-NEXT:    [[__BEGIN1:%.*]] = alloca ptr, align 8
// CHECK-NEXT:    [[__END1:%.*]] = alloca ptr, align 8
// CHECK-NEXT:    [[I:%.*]] = alloca i32, align 4
// CHECK-NEXT:    store ptr [[E:%.*]], ptr [[E_ADDR]], align 8, !tbaa [[TBAA14:![0-9]+]]
// CHECK-NEXT:    call void @llvm.lifetime.start.p0(i64 8, ptr [[__RANGE1]]) #[[ATTR3]]
// CHECK-NEXT:    [[TMP0:%.*]] = load ptr, ptr [[E_ADDR]], align 8, !tbaa [[TBAA14]]
// CHECK-NEXT:    store ptr [[TMP0]], ptr [[__RANGE1]], align 8, !tbaa [[TBAA14]]
// CHECK-NEXT:    call void @llvm.lifetime.start.p0(i64 8, ptr [[__BEGIN1]]) #[[ATTR3]]
// CHECK-NEXT:    [[TMP1:%.*]] = load ptr, ptr [[__RANGE1]], align 8, !tbaa [[TBAA14]]
// CHECK-NEXT:    [[ARRAYDECAY:%.*]] = getelementptr inbounds [4 x i32], ptr [[TMP1]], i64 0, i64 0
// CHECK-NEXT:    store ptr [[ARRAYDECAY]], ptr [[__BEGIN1]], align 8, !tbaa [[TBAA14]]
// CHECK-NEXT:    call void @llvm.lifetime.start.p0(i64 8, ptr [[__END1]]) #[[ATTR3]]
// CHECK-NEXT:    [[TMP2:%.*]] = load ptr, ptr [[__RANGE1]], align 8, !tbaa [[TBAA14]]
// CHECK-NEXT:    [[ARRAYDECAY1:%.*]] = getelementptr inbounds [4 x i32], ptr [[TMP2]], i64 0, i64 0
// CHECK-NEXT:    [[ADD_PTR:%.*]] = getelementptr inbounds i32, ptr [[ARRAYDECAY1]], i64 4
// CHECK-NEXT:    store ptr [[ADD_PTR]], ptr [[__END1]], align 8, !tbaa [[TBAA14]]
// CHECK-NEXT:    br label [[FOR_COND:%.*]]
// CHECK:       for.cond:
// CHECK-NEXT:    [[TMP3:%.*]] = load ptr, ptr [[__BEGIN1]], align 8, !tbaa [[TBAA14]]
// CHECK-NEXT:    [[TMP4:%.*]] = load ptr, ptr [[__END1]], align 8, !tbaa [[TBAA14]]
// CHECK-NEXT:    [[CMP:%.*]] = icmp ne ptr [[TMP3]], [[TMP4]]
// CHECK-NEXT:    [[CMP_EXPVAL:%.*]] = call i1 @llvm.expect.i1(i1 [[CMP]], i1 true)
// CHECK-NEXT:    br i1 [[CMP_EXPVAL]], label [[FOR_BODY:%.*]], label [[FOR_COND_CLEANUP:%.*]]
// CHECK:       for.cond.cleanup:
// CHECK-NEXT:    call void @llvm.lifetime.end.p0(i64 8, ptr [[__END1]]) #[[ATTR3]]
// CHECK-NEXT:    call void @llvm.lifetime.end.p0(i64 8, ptr [[__BEGIN1]]) #[[ATTR3]]
// CHECK-NEXT:    call void @llvm.lifetime.end.p0(i64 8, ptr [[__RANGE1]]) #[[ATTR3]]
// CHECK-NEXT:    br label [[FOR_END:%.*]]
// CHECK:       for.body:
// CHECK-NEXT:    call void @llvm.lifetime.start.p0(i64 4, ptr [[I]]) #[[ATTR3]]
// CHECK-NEXT:    [[TMP5:%.*]] = load ptr, ptr [[__BEGIN1]], align 8, !tbaa [[TBAA14]]
// CHECK-NEXT:    [[TMP6:%.*]] = load i32, ptr [[TMP5]], align 4, !tbaa [[TBAA2]]
// CHECK-NEXT:    store i32 [[TMP6]], ptr [[I]], align 4, !tbaa [[TBAA2]]
// CHECK-NEXT:    call void @llvm.lifetime.end.p0(i64 4, ptr [[I]]) #[[ATTR3]]
// CHECK-NEXT:    br label [[FOR_INC:%.*]]
// CHECK:       for.inc:
// CHECK-NEXT:    [[TMP7:%.*]] = load ptr, ptr [[__BEGIN1]], align 8, !tbaa [[TBAA14]]
// CHECK-NEXT:    [[INCDEC_PTR:%.*]] = getelementptr inbounds nuw i32, ptr [[TMP7]], i32 1
// CHECK-NEXT:    store ptr [[INCDEC_PTR]], ptr [[__BEGIN1]], align 8, !tbaa [[TBAA14]]
// CHECK-NEXT:    br label [[FOR_COND]], !llvm.loop [[LOOP16:![0-9]+]]
// CHECK:       for.end:
// CHECK-NEXT:    ret void
//
void frl(int (&&e) [4])
{
  for(int i : e) [[likely]];
}

// CHECK-LABEL: @_Z3fruOA4_i(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[E_ADDR:%.*]] = alloca ptr, align 8
// CHECK-NEXT:    [[__RANGE1:%.*]] = alloca ptr, align 8
// CHECK-NEXT:    [[__BEGIN1:%.*]] = alloca ptr, align 8
// CHECK-NEXT:    [[__END1:%.*]] = alloca ptr, align 8
// CHECK-NEXT:    [[I:%.*]] = alloca i32, align 4
// CHECK-NEXT:    store ptr [[E:%.*]], ptr [[E_ADDR]], align 8, !tbaa [[TBAA14]]
// CHECK-NEXT:    call void @llvm.lifetime.start.p0(i64 8, ptr [[__RANGE1]]) #[[ATTR3]]
// CHECK-NEXT:    [[TMP0:%.*]] = load ptr, ptr [[E_ADDR]], align 8, !tbaa [[TBAA14]]
// CHECK-NEXT:    store ptr [[TMP0]], ptr [[__RANGE1]], align 8, !tbaa [[TBAA14]]
// CHECK-NEXT:    call void @llvm.lifetime.start.p0(i64 8, ptr [[__BEGIN1]]) #[[ATTR3]]
// CHECK-NEXT:    [[TMP1:%.*]] = load ptr, ptr [[__RANGE1]], align 8, !tbaa [[TBAA14]]
// CHECK-NEXT:    [[ARRAYDECAY:%.*]] = getelementptr inbounds [4 x i32], ptr [[TMP1]], i64 0, i64 0
// CHECK-NEXT:    store ptr [[ARRAYDECAY]], ptr [[__BEGIN1]], align 8, !tbaa [[TBAA14]]
// CHECK-NEXT:    call void @llvm.lifetime.start.p0(i64 8, ptr [[__END1]]) #[[ATTR3]]
// CHECK-NEXT:    [[TMP2:%.*]] = load ptr, ptr [[__RANGE1]], align 8, !tbaa [[TBAA14]]
// CHECK-NEXT:    [[ARRAYDECAY1:%.*]] = getelementptr inbounds [4 x i32], ptr [[TMP2]], i64 0, i64 0
// CHECK-NEXT:    [[ADD_PTR:%.*]] = getelementptr inbounds i32, ptr [[ARRAYDECAY1]], i64 4
// CHECK-NEXT:    store ptr [[ADD_PTR]], ptr [[__END1]], align 8, !tbaa [[TBAA14]]
// CHECK-NEXT:    br label [[FOR_COND:%.*]]
// CHECK:       for.cond:
// CHECK-NEXT:    [[TMP3:%.*]] = load ptr, ptr [[__BEGIN1]], align 8, !tbaa [[TBAA14]]
// CHECK-NEXT:    [[TMP4:%.*]] = load ptr, ptr [[__END1]], align 8, !tbaa [[TBAA14]]
// CHECK-NEXT:    [[CMP:%.*]] = icmp ne ptr [[TMP3]], [[TMP4]]
// CHECK-NEXT:    [[CMP_EXPVAL:%.*]] = call i1 @llvm.expect.i1(i1 [[CMP]], i1 false)
// CHECK-NEXT:    br i1 [[CMP_EXPVAL]], label [[FOR_BODY:%.*]], label [[FOR_COND_CLEANUP:%.*]]
// CHECK:       for.cond.cleanup:
// CHECK-NEXT:    call void @llvm.lifetime.end.p0(i64 8, ptr [[__END1]]) #[[ATTR3]]
// CHECK-NEXT:    call void @llvm.lifetime.end.p0(i64 8, ptr [[__BEGIN1]]) #[[ATTR3]]
// CHECK-NEXT:    call void @llvm.lifetime.end.p0(i64 8, ptr [[__RANGE1]]) #[[ATTR3]]
// CHECK-NEXT:    br label [[FOR_END:%.*]]
// CHECK:       for.body:
// CHECK-NEXT:    call void @llvm.lifetime.start.p0(i64 4, ptr [[I]]) #[[ATTR3]]
// CHECK-NEXT:    [[TMP5:%.*]] = load ptr, ptr [[__BEGIN1]], align 8, !tbaa [[TBAA14]]
// CHECK-NEXT:    [[TMP6:%.*]] = load i32, ptr [[TMP5]], align 4, !tbaa [[TBAA2]]
// CHECK-NEXT:    store i32 [[TMP6]], ptr [[I]], align 4, !tbaa [[TBAA2]]
// CHECK-NEXT:    call void @llvm.lifetime.end.p0(i64 4, ptr [[I]]) #[[ATTR3]]
// CHECK-NEXT:    br label [[FOR_INC:%.*]]
// CHECK:       for.inc:
// CHECK-NEXT:    [[TMP7:%.*]] = load ptr, ptr [[__BEGIN1]], align 8, !tbaa [[TBAA14]]
// CHECK-NEXT:    [[INCDEC_PTR:%.*]] = getelementptr inbounds nuw i32, ptr [[TMP7]], i32 1
// CHECK-NEXT:    store ptr [[INCDEC_PTR]], ptr [[__BEGIN1]], align 8, !tbaa [[TBAA14]]
// CHECK-NEXT:    br label [[FOR_COND]], !llvm.loop [[LOOP17:![0-9]+]]
// CHECK:       for.end:
// CHECK-NEXT:    ret void
//
void fru(int (&&e) [4])
{
  for(int i : e) [[unlikely]];
}
