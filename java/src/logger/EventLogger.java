package logger;

import constants.Constants;

import java.util.ArrayList;
import java.util.List;

public class EventLogger {
    private static EventLogger instance;
    private final List<LogEntry> logs = new ArrayList<>();
    private final List<EventLoggerListener> listeners = new ArrayList<>();
    private long lastNotifyTime = 0;

    private EventLogger() {}

    public static synchronized EventLogger getInstance() {
        if (instance == null) {
            instance = new EventLogger();
        }
        return instance;
    }

public synchronized void log(String message) {
    LogEntry entry = new LogEntry(message);
    logs.add(entry);
    long now = System.currentTimeMillis();
    if (lastNotifyTime == 0 || now - lastNotifyTime > Constants.logNotifyInterval) {
        notifyListeners();
        lastNotifyTime = now;
    }
}

    public synchronized List<LogEntry> getLogs() {
        return new ArrayList<>(logs);
    }

    public synchronized void clear() {
        logs.clear();
//        notifyListeners();
    }

    public synchronized void addListener(EventLoggerListener listener) {
        listeners.add(listener);
        listener.onLogChanged(getLogs());
    }

    public synchronized void removeListener(EventLoggerListener listener) {
        listeners.remove(listener);
    }

    private void notifyListeners() {
        List<LogEntry> copy = getLogs();
        for (EventLoggerListener listener : listeners) {
            listener.onLogChanged(copy);
        }
    }
}
