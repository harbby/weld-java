package weld;

import org.junit.Assert;
import org.junit.Test;

import static weld.WeldStruct.struct;
import static weld.WeldVec.vec;
import static weld.types.PrimitiveType.i32;
import static weld.types.VecType.vecOf;

public class VectorArrayTest {
    private static final int BATCH_SIZE = 2048;

    public static WeldValue getIntVector(int batSize) {
        long address = Platform.allocateMemory((batSize << 2));

        long buffer = Platform.allocateMemory(16);
        Platform.putLong(buffer, address);
        Platform.putLong(buffer + 8, batSize);

        for (int i = 0; i < batSize; i++) {
            Platform.putInt((i << 2) + address, i + 1);
        }
        return new WeldValue(buffer, 16);
    }

    @Test
    public void compileAndRun0ArgsScalarRet() {
        String code = "|x:vec[i32]| result(for(x, merger[i64,+], |b,i,e| merge(b, i64(e))))";
        WeldValue value = getIntVector(5);
        //final WeldValue value2 = struct(vec(1, 2, 3, 4, 5)).toValue();
        //long p = value.getPointer();

        try (final WeldModule module = WeldModule.compile(code);
             final WeldValue output = module.run(value)) {
            final WeldStruct struct = output.result(i32);
            Assert.assertEquals(15, struct.getInt(0));
        }
    }

    @Test
    public void compileAndRunVecAddValue() {
        final String add2 =
                "|ys:vec[i32]|" +
                        "let rows = result(for(ys, appender[i32], |b, i, y| merge(b, y + 1)));" +
                        "{rows}";
        final WeldValue value = getIntVector(2048);
        try (final WeldModule module = WeldModule.compile(add2)) {
            WeldValue rs = module.run(value);
            final WeldVec v1 = rs.result(vecOf(i32)).getVec(0);
            Assert.assertEquals(2, v1.getInt(0));
            Assert.assertEquals(3, v1.getInt(1));
            Assert.assertEquals(4, v1.getInt(2));
        }
    }

    @Test
    public void compileAndRunVecDoubleAdd() {
        final String add2 =
                "|ys:vec[i32]|" +
                        "let rows = result(for(ys, appender[i32], |b, i, y| merge(b, y + 1)));" +
                        "let a = result(for(rows, appender[i32], |b, i, n| merge(b,  n + 5)));" +
                        "let b = result(for(a, appender[i32], |b, i, n| merge(b, n + 10)));" +
                        "{b}";
        final WeldValue value = struct(vec(1, 3, 4)).toValue();
        try (final WeldModule module = WeldModule.compile(add2)) {
            WeldValue rs = module.run(value);
            final WeldVec v1 = rs.result(vecOf(i32)).getVec(0);
            Assert.assertEquals(17, v1.getInt(0));
            Assert.assertEquals(19, v1.getInt(1));
            Assert.assertEquals(20, v1.getInt(2));
        }
    }

}
