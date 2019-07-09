
if __name__ == '__main__':
    try:
        import sys

        def freq_wrapper(signal, fs):
            freq = freq_from_fft(signal, fs)
            print('%f Hz' % freq)

        files = sys.argv[1:]
        if files:
            for filename in files:
                try:
                    start_time = time()
                    analyze_channels(filename, freq_wrapper)
                    print('\nTime elapsed: %.3f s\n' % (time() - start_time))

                except IOError:
                    print('Couldn\'t analyze "' + filename + '"\n')
                print('')
        else:
            sys.exit("You must provide at least one file to analyze")
    except BaseException as e:
        print('Error:')
        print(e)
        raise
    finally:
        # Otherwise Windows closes the window too quickly to read
        input('(Press <Enter> to close)')
