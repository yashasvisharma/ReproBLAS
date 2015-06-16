import tests.benchs.benchs as benchs
import tests.harness.harness as harness

bench_harness = harness.Harness("bench")
params = ["N", "a", "u", "fold", "preN"]
ranges = [[4096], [10000], [0], [3], [1024]]
attribute = "freq"
#attribute = "time"
#bench_harness.add_suite(benchs.BenchSuite([benchs.BenchRDSUMTest(), benchs.BenchRDASUMTest(), benchs.BenchRDNRM2Test(), benchs.BenchRDDOTTest()], params, ranges, attribute))
#bench_harness.add_suite(benchs.BenchSuite([benchs.BenchRSSUMTest(), benchs.BenchRSASUMTest(), benchs.BenchRSNRM2Test(), benchs.BenchRSDOTTest()], params, ranges, attribute))
#bench_harness.add_suite(benchs.BenchSuite([benchs.BenchRZSUMTest(), benchs.BenchRDZASUMTest(), benchs.BenchRDZNRM2Test(), benchs.BenchRZDOTUTest(), benchs.BenchRZDOTCTest()], params, ranges, attribute))
#bench_harness.add_suite(benchs.BenchSuite([benchs.BenchRCSUMTest(), benchs.BenchRSCASUMTest(), benchs.BenchRSCNRM2Test(), benchs.BenchRCDOTUTest(), benchs.BenchRCDOTCTest()], params, ranges, attribute))
#bench_harness.add_suite(benchs.BenchSuite([benchs.BenchDDICONVTest(), benchs.BenchZZICONVTest(), benchs.BenchSSICONVTest(), benchs.BenchCCICONVTest()], params, ranges, attribute))
bench_harness.add_suite(benchs.BenchSuite([benchs.BenchDIDIADDTest(), benchs.BenchRDSUMTest()], params, ranges, attribute))
bench_harness.add_suite(benchs.BenchSuite([benchs.BenchZIZIADDTest(), benchs.BenchRZSUMTest()], params, ranges, attribute))
bench_harness.add_suite(benchs.BenchSuite([benchs.BenchSISIADDTest(), benchs.BenchRSSUMTest()], params, ranges, attribute))
bench_harness.add_suite(benchs.BenchSuite([benchs.BenchCICIADDTest(), benchs.BenchRCSUMTest()], params, ranges, attribute))
bench_harness.run()
