package logger;

import java.util.List;

public interface EventLoggerListener {
    void onLogChanged(List<LogEntry> logs);
}
