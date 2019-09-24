<template>
  <div class="columns">
    <div class="column">
      <device-info></device-info>
    </div>
    <div class="column">
      <device-settings></device-settings>
    </div>
  </div>
</template>

<script>
import DeviceInfo from './DeviceInfo';
import DeviceSettings from './DeviceSettings';

export default {
  components: {
    DeviceInfo,
    DeviceSettings,
  },
  data() {
    return {};
  },
};
</script>
