<template>
  <div class="modal-card" style="">
    <b-loading
      :is-full-page="true"
      can-cancel
      :active.sync="isLoading"
    ></b-loading>

    <header class="modal-card-head">
      <p class="modal-card-title">WiFi Mode Setting</p>
    </header>
    <section class="modal-card-body">
      <p class="label">Are you sure to change the WiFi mode from</p>
      <b-field class="level" grouped>
        <b-select :value="deviceSettings.wifiMode" disabled>
          <option v-for="v in wifiModes" :value="v.value" :key="v.label">
            {{ v.label }}
          </option>
        </b-select>
        <p class="control">to</p>
        <b-select v-model="settings.wifiMode">
          <option v-for="v in selectableModes" :value="v.value" :key="v.label">
            {{ v.label }}
          </option>
        </b-select>
      </b-field>

      <p class="label">Related settings</p>
      <b-field class="level" grouped>
        <p class="control">AP SSID (Host)</p>
        <b-input
          class="control"
          :value="deviceSettings.hApName"
          expanded
          disabled
        ></b-input>
      </b-field>

      <b-field
        class="level"
        grouped
        :type="!deviceSettings.cApName ? 'is-danger' : ''"
      >
        <p class="control">STA SSID (Client)</p>
        <b-input
          class="control"
          :value="deviceSettings.cApName || 'N/A'"
          expanded
          disabled
        ></b-input>
      </b-field>

      <p class="has-text-danger" v-if="!isValidMode">
        * To choose STA mode, you have to setup Client AP first.
      </p>
      <p class="has-text-danger">
        * You have to reboot the device to apply the settings.
      </p>
    </section>
    <footer class="modal-card-foot">
      <b-button @click="$parent.close()">
        Cancel
      </b-button>
      <b-button class="is-primary" @click="save" :disabled="!isValidMode">
        Save
      </b-button>
    </footer>
  </div>
</template>

<script>
import { mapActions, mapState } from 'vuex';

const wifiModes = [
  {
    label: 'AP (Host)',
    value: 2,
  },
  {
    label: 'STA (Client)',
    value: 1,
  },
  {
    label: 'AP+STA (Host+Client)',
    value: 3,
  },
];

export default {
  data() {
    return {
      isLoading: false,
      settings: {
        wifiMode: 1,
      },
      wifiModes,
    };
  },
  computed: {
    ...mapState(['deviceSettings']),
    selectableModes() {
      return wifiModes.filter(v => v.value !== this.deviceSettings.wifiMode);
    },
    isValidMode() {
      const selectedMode = this.settings.wifiMode;
      if (
        !this.deviceSettings.cApName &&
        (selectedMode == 3 || selectedMode == 1)
      ) {
        return false;
      }
      return true;
    },
  },
  methods: {
    ...mapActions(['postDeviceSettings', 'fetchScanResults']),
    signalToLabel(v) {
      if (v < 2) {
        return 'is-danger';
      } else if (v < 3) {
        return 'is-warn';
      }
      return 'is-success';
    },
    onClickAP(ap) {
      this.settings.cApName = ap.ssid;
    },
    async save() {
      console.log(this.settings);
      this.isLoading = true;
      const newSetting = { ...this.deviceSettings, ...this.settings };
      await this.postDeviceSettings(newSetting);
      this.isLoading = false;
      this.$buefy.snackbar.open({
        message: 'You have to reboot the device to apply the settings.',
        type: 'is-warning',
        position: 'is-bottom-right',
        actionText: 'OK',
        indefinite: true,
      });
      this.$parent.close();
    },
  },
  mounted() {
    this.settings.wifiMode = this.selectableModes[0].value;
  },
};
</script>

<style scoped lang="scss">
.scan-header {
  align-items: center;
  justify-content: space-between;
  display: flex;
}
.ap-panel {
  display: flex;
  flex-wrap: wrap;
  p {
    flex: 1 1 auto;
  }
}
.noresult-panel {
  justify-content: center;
}
</style>
